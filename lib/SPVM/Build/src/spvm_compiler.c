#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_sub.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_sub.h"
#include "spvm_field.h"
#include "spvm_package_var.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_sub.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_COMPILER));
  
  // Allocator
  compiler->allocator = SPVM_COMPILER_ALLOCATOR_new(compiler);

  compiler->bufptr = "";

  compiler->name_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Parser information
  compiler->op_use_stack = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->op_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->basic_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->basic_type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->subs = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->packages = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->package_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->package_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->package_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->op_constants = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->module_include_pathes = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->opcode_array = SPVM_OPCODE_ARRAY_new(compiler);

  // Add basic types
  SPVM_COMPILER_add_basic_types(compiler);

  // use SPVM::CORE module
  SPVM_OP* op_name_core = SPVM_OP_new_op_name(compiler, "SPVM::CORE", "SPVM::CORE", 0);
  SPVM_OP* op_type_core = SPVM_OP_build_basic_type(compiler, op_name_core);
  SPVM_OP* op_use_core = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name_core->file, op_name_core->line);
  SPVM_OP_build_use(compiler, op_use_core, op_type_core);
  SPVM_LIST_push(compiler->op_use_stack, op_use_core);

  return compiler;
}

int32_t SPVM_COMPILER_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string) {
  
  
  int32_t id = runtime->strings_length;
  if (runtime->strings_length >= runtime->strings_capacity) {
    int32_t new_strings_capacity = runtime->strings_capacity * 2;
    char** new_strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_strings_capacity);
    memcpy(new_strings, runtime->strings, sizeof(char*) * runtime->strings_length);
    free(runtime->strings);
    runtime->strings = new_strings;
    runtime->strings_capacity = new_strings_capacity;
  }
  
  runtime->strings[runtime->strings_length] = string;
  runtime->strings_length++;
  
  return id;
}

void SPVM_COMPILER_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type) {
  
  if (runtime->portable_basic_types_length >= runtime->portable_basic_types_capacity) {
    int32_t new_portable_basic_types_capacity = runtime->portable_basic_types_capacity * 2;
    int32_t* new_portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * new_portable_basic_types_capacity);
    memcpy(new_portable_basic_types, runtime->portable_basic_types, sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_length);
    free(runtime->portable_basic_types);
    runtime->portable_basic_types = new_portable_basic_types;
    runtime->portable_basic_types_capacity = new_portable_basic_types_capacity;
  }
  
  int32_t* new_portable_basic_type = (int32_t*)&runtime->portable_basic_types[runtime->portable_basic_types_unit * runtime->portable_basic_types_length];
  new_portable_basic_type[0] = SPVM_COMPILER_push_runtime_string(compiler, runtime, basic_type->name);
  new_portable_basic_type[1] = basic_type->id;
  new_portable_basic_type[2] = basic_type->category;
  if (basic_type->package) {
    new_portable_basic_type[3] = basic_type->package->id;
  }
  else {
    new_portable_basic_type[3] = -1;
  }
  runtime->portable_basic_types_length++;
}

void SPVM_COMPILER_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field) {
  
  if (runtime->portable_fields_length >= runtime->portable_fields_capacity) {
    int32_t new_portable_fields_capacity = runtime->portable_fields_capacity * 2;
    int32_t* new_portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * new_portable_fields_capacity);
    memcpy(new_portable_fields, runtime->portable_fields, sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_length);
    free(runtime->portable_fields);
    runtime->portable_fields = new_portable_fields;
    runtime->portable_fields_capacity = new_portable_fields_capacity;
  }
  
  int32_t* new_portable_field = (int32_t*)&runtime->portable_fields[runtime->portable_fields_unit * runtime->portable_fields_length];

  new_portable_field[0] = field->id;
  new_portable_field[1] = field->index;
  new_portable_field[2] = field->flag;
  new_portable_field[3] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->name);
  new_portable_field[4] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->abs_name);
  new_portable_field[5] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->signature);
  if (field->type->basic_type) {
    new_portable_field[6] = field->type->basic_type->id;
  }
  else {
    new_portable_field[6] = -1;
  }
  new_portable_field[7] = field->type->dimension;
  new_portable_field[8] = field->type->flag;
  if (field->package) {
    new_portable_field[9] = field->package->id;
  }
  else {
    new_portable_field[9] = -1;
  }
  
  runtime->portable_fields_length++;
}

void SPVM_COMPILER_push_portable_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE_VAR* package_var) {
  
  if (runtime->portable_package_vars_length >= runtime->portable_package_vars_capacity) {
    int32_t new_portable_package_vars_capacity = runtime->portable_package_vars_capacity * 2;
    int32_t* new_portable_package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_package_vars_unit * new_portable_package_vars_capacity);
    memcpy(new_portable_package_vars, runtime->portable_package_vars, sizeof(int32_t) * runtime->portable_package_vars_unit * runtime->portable_package_vars_length);
    free(runtime->portable_package_vars);
    runtime->portable_package_vars = new_portable_package_vars;
    runtime->portable_package_vars_capacity = new_portable_package_vars_capacity;
  }
  
  int32_t* new_portable_package_var = (int32_t*)&runtime->portable_package_vars[runtime->portable_package_vars_unit * runtime->portable_package_vars_length];

  new_portable_package_var[0] = package_var->id;
  new_portable_package_var[1] = SPVM_COMPILER_push_runtime_string(compiler, runtime, package_var->name);
  new_portable_package_var[2] = SPVM_COMPILER_push_runtime_string(compiler, runtime, package_var->abs_name);
  new_portable_package_var[3] = SPVM_COMPILER_push_runtime_string(compiler, runtime, package_var->signature);
  if (package_var->type->basic_type) {
    new_portable_package_var[4] = package_var->type->basic_type->id;
  }
  else {
    new_portable_package_var[4] = -1;
  }
  new_portable_package_var[5] = package_var->type->dimension;
  new_portable_package_var[6] = package_var->type->flag;
  if (package_var->package) {
    new_portable_package_var[7] = package_var->package->id;
  }
  else {
    new_portable_package_var[7] = -1;
  }
  
  runtime->portable_package_vars_length++;
}

void SPVM_COMPILER_push_portable_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_SUB* sub) {
  
  if (runtime->portable_subs_length >= runtime->portable_subs_capacity) {
    int32_t new_portable_subs_capacity = runtime->portable_subs_capacity * 2;
    int32_t* new_portable_subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_subs_unit * new_portable_subs_capacity);
    memcpy(new_portable_subs, runtime->portable_subs, sizeof(int32_t) * runtime->portable_subs_unit * runtime->portable_subs_length);
    free(runtime->portable_subs);
    runtime->portable_subs = new_portable_subs;
    runtime->portable_subs_capacity = new_portable_subs_capacity;
  }
  
  int32_t* new_portable_sub = (int32_t*)&runtime->portable_subs[runtime->portable_subs_unit * runtime->portable_subs_length];

  new_portable_sub[0] = sub->id;
  new_portable_sub[1] = sub->flag;
  new_portable_sub[2] = SPVM_COMPILER_push_runtime_string(compiler, runtime, sub->name);
  new_portable_sub[3] = SPVM_COMPILER_push_runtime_string(compiler, runtime, sub->abs_name);
  new_portable_sub[4] = SPVM_COMPILER_push_runtime_string(compiler, runtime, sub->signature);
  if (sub->package) {
    new_portable_sub[5] = sub->package->id;
  }
  else {
    new_portable_sub[5] = -1;
  }
  
  runtime->portable_subs_length++;
}

void SPVM_COMPILER_push_portable_package(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE* package) {
  
  if (runtime->portable_packages_length >= runtime->portable_packages_capacity) {
    int32_t new_portable_packages_capacity = runtime->portable_packages_capacity * 2;
    int32_t* new_portable_packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_packages_unit * new_portable_packages_capacity);
    memcpy(new_portable_packages, runtime->portable_packages, sizeof(int32_t) * runtime->portable_packages_unit * runtime->portable_packages_length);
    free(runtime->portable_packages);
    runtime->portable_packages = new_portable_packages;
    runtime->portable_packages_capacity = new_portable_packages_capacity;
  }
  
  int32_t* new_portable_package = (int32_t*)&runtime->portable_packages[runtime->portable_packages_unit * runtime->portable_packages_length];

  new_portable_package[0] = package->id;
  new_portable_package[1] = SPVM_COMPILER_push_runtime_string(compiler, runtime, package->name);
  if (package->sub_destructor) {
    new_portable_package[2] = package->sub_destructor->id;
  }
  else {
    new_portable_package[2] = -1;
  }
  
  runtime->portable_packages_length++;
}

void SPVM_COMPILER_build_runtime_info(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  
  // build runtime basic types
  for (size_t i = 0; i < runtime->portable_basic_types_unit * runtime->portable_basic_types_length; i += runtime->portable_basic_types_unit) {
    int32_t* portable_basic_type = (int32_t*)&runtime->portable_basic_types[i];
    
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_RUNTIME_BASIC_TYPE_new();
    runtime_basic_type->name = runtime->strings[portable_basic_type[0]];
    runtime_basic_type->id = portable_basic_type[1];
    runtime_basic_type->category = portable_basic_type[2];
    runtime_basic_type->package_id = portable_basic_type[3];
    
    SPVM_LIST_push(runtime->runtime_basic_types, runtime_basic_type);
  }
  
  // build runtime basic type symtable
  for (int32_t basic_type_id = 0; basic_type_id < runtime->runtime_basic_types->length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_LIST_fetch(runtime->runtime_basic_types, basic_type_id);
    SPVM_HASH_insert(runtime->runtime_basic_type_symtable, runtime_basic_type->name, strlen(runtime_basic_type->name), runtime_basic_type);
  }
  
  // build_runtime fields
  for (size_t i = 0; i < runtime->portable_fields_unit * runtime->portable_fields_length; i += runtime->portable_fields_unit) {
    int32_t* portable_field = (int32_t*)&runtime->portable_fields[i];
    
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_RUNTIME_FIELD_new(compiler);
    runtime_field->id = portable_field[0];
    runtime_field->index = portable_field[1];
    runtime_field->flag = portable_field[2];
    runtime_field->name = runtime->strings[portable_field[3]];
    runtime_field->abs_name = runtime->strings[portable_field[4]];
    runtime_field->signature = runtime->strings[portable_field[5]];
    runtime_field->basic_type_id = portable_field[6];
    runtime_field->type_dimension = portable_field[7];
    runtime_field->type_flag = portable_field[8];
    runtime_field->package_id = portable_field[9];
    
    SPVM_LIST_push(runtime->runtime_fields, runtime_field);
  }
  
  // build runtime field symtable
  for (int32_t field_id = 0; field_id < runtime->runtime_fields->length; field_id++) {
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_LIST_fetch(runtime->runtime_fields, field_id);
    SPVM_HASH_insert(runtime->runtime_field_symtable, runtime_field->name, strlen(runtime_field->name), runtime_field);
  }

  // build package variables
  for (size_t i = 0; i < runtime->portable_package_vars_unit * runtime->portable_package_vars_length; i += runtime->portable_package_vars_unit) {
    int32_t* portable_package_var = (int32_t*)&runtime->portable_package_vars[i];
    
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_RUNTIME_PACKAGE_VAR_new(compiler);
    runtime_package_var->id = portable_package_var[0];
    runtime_package_var->name = runtime->strings[portable_package_var[1]];
    runtime_package_var->abs_name = runtime->strings[portable_package_var[2]];
    runtime_package_var->signature = runtime->strings[portable_package_var[3]];
    runtime_package_var->basic_type_id = portable_package_var[4];
    runtime_package_var->type_dimension = portable_package_var[5];
    runtime_package_var->type_flag = portable_package_var[6];
    runtime_package_var->package_id = portable_package_var[7];
    
    SPVM_LIST_push(runtime->runtime_package_vars, runtime_package_var);
  }

  // build package variable symtable
  for (int32_t package_var_id = 0; package_var_id < runtime->runtime_package_vars->length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_LIST_fetch(runtime->runtime_package_vars, package_var_id);
    SPVM_HASH_insert(runtime->runtime_package_var_symtable, runtime_package_var->name, strlen(runtime_package_var->name), runtime_package_var);
  }

  // build subs
  for (size_t i = 0; i < runtime->portable_subs_unit * runtime->portable_subs_length; i += runtime->portable_subs_unit) {
    int32_t* portable_sub = (int32_t*)&runtime->portable_subs[i];
    
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_RUNTIME_SUB_new(compiler);
    runtime_sub->id = portable_sub[0];
    runtime_sub->flag = portable_sub[1];
    runtime_sub->name = runtime->strings[portable_sub[2]];
    runtime_sub->abs_name = runtime->strings[portable_sub[3]];
    runtime_sub->signature = runtime->strings[portable_sub[4]];
    runtime_sub->package_id = portable_sub[5];
    
    SPVM_LIST_push(runtime->runtime_subs, runtime_sub);
  }

  // build sub symtable
  for (int32_t sub_id = 0; sub_id < runtime->runtime_subs->length; sub_id++) {
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_LIST_fetch(runtime->runtime_subs, sub_id);
    SPVM_HASH_insert(runtime->runtime_sub_symtable, runtime_sub->name, strlen(runtime_sub->name), runtime_sub);
  }

  // build packages
  for (size_t i = 0; i < runtime->portable_packages_unit * runtime->portable_packages_length; i += runtime->portable_packages_unit) {
    int32_t* portable_package = (int32_t*)&runtime->portable_packages[i];
    
    SPVM_RUNTIME_PACKAGE* runtime_package = SPVM_RUNTIME_SUB_new(compiler);
    runtime_package->id = portable_package[0];
    runtime_package->name = runtime->strings[portable_package[1]];
    runtime_package->destructor_sub_id = portable_package[2];
    
    SPVM_LIST_push(runtime->runtime_packages, runtime_package);
  }

  // build package symtable
  for (int32_t package_id = 0; package_id < runtime->runtime_packages->length; package_id++) {
    SPVM_RUNTIME_SUB* runtime_package = SPVM_LIST_fetch(runtime->runtime_packages, package_id);
    SPVM_HASH_insert(runtime->runtime_package_symtable, runtime_package->name, strlen(runtime_package->name), runtime_package);
  }
}

SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  SPVM_ENV* env = (SPVM_ENV*)SPVM_RUNTIME_API_get_env_runtime();
  
  runtime->env = env;

  runtime->compiler = compiler;
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(env, runtime);
  
  // Initialize Package Variables
  runtime->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (compiler->package_vars->length + 1));

  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  runtime->strings_capacity = 32;
  
  runtime->strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * runtime->strings_capacity);
  
  // Portable basic type
  runtime->portable_basic_types_capacity = 8;
  runtime->portable_basic_types_unit = 4;
  runtime->portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_capacity);
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_COMPILER_push_portable_basic_type(compiler, runtime, basic_type);
  }
  
  // Build runtime basic type infos
  runtime->runtime_basic_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_basic_type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Portable fields
  runtime->portable_fields_capacity = 8;
  runtime->portable_fields_unit = 10;
  runtime->portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_capacity);
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_BASIC_TYPE* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_COMPILER_push_portable_field(compiler, runtime, field);
  }
  
  // Build runtime field infos
  runtime->runtime_fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Portable package_vars
  runtime->portable_package_vars_capacity = 8;
  runtime->portable_package_vars_unit = 8;
  runtime->portable_package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_package_vars_unit * runtime->portable_package_vars_capacity);
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_BASIC_TYPE* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    SPVM_COMPILER_push_portable_package_var(compiler, runtime, package_var);
  }
  
  // Build runtime package_var infos
  runtime->runtime_package_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_package_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Portable subs
  runtime->portable_subs_capacity = 8;
  runtime->portable_subs_unit = 6;
  runtime->portable_subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_subs_unit * runtime->portable_subs_capacity);
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_BASIC_TYPE* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
    SPVM_COMPILER_push_portable_sub(compiler, runtime, sub);
  }
  
  // Build runtime sub infos
  runtime->runtime_subs = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Portable packages
  runtime->portable_packages_capacity = 8;
  runtime->portable_packages_unit = 3;
  runtime->portable_packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_packages_unit * runtime->portable_packages_capacity);
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_BASIC_TYPE* package = SPVM_LIST_fetch(compiler->packages, package_id);
    SPVM_COMPILER_push_portable_package(compiler, runtime, package);
  }
  
  // Build runtime package infos
  runtime->runtime_packages = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_package_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  SPVM_COMPILER_build_runtime_info(compiler, runtime);

  return runtime;
}

void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler) {
  // Add unknown basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_UNKNOWN;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  // Add undef basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_UNDEF;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add void basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_VOID;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  // Add byte basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_BYTE;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add short basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_SHORT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add int basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_INT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add long basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_LONG;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add float basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_FLOAT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add double basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add Object basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_ANY_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
}

void SPVM_COMPILER_compile(SPVM_COMPILER* compiler) {

  // If this is set to 1, you can see yacc parsing result
#ifdef SPVM_DEBUG_YACC
  SPVM_yydebug = 1;
#else
  SPVM_yydebug = 0;
#endif
  
  /* call SPVM_yyparse */
  int32_t parse_error_flag = SPVM_yyparse(compiler);
  if (parse_error_flag) {
    compiler->error_count++;
  }
  
  if (compiler->error_count == 0) {
    // Check syntax
    SPVM_OP_CHECKER_check(compiler);

    // Build bytecode
    if (compiler->error_count == 0) {
      SPVM_OPCODE_BUILDER_build_opcode_array(compiler);
    }
  }
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {
  
  // Free allocator
  SPVM_COMPILER_ALLOCATOR_free(compiler);
  
  // Free opcode array
  SPVM_OPCODE_ARRAY_free(compiler, compiler->opcode_array);
  
  free(compiler);
}

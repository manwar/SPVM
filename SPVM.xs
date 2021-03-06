#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"
#include "spvm_object.h"
#include "spvm_native.h"
#include "spvm_opcode_builder.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_list.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_string_buffer.h"
#include "spvm_use.h"
#include "spvm_limit.h"
#include "spvm_portable.h"

#include "spvm_runtime_sub.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_arg.h"

#include "spvm_portable.h"
#include "spvm_csource_builder_exe.h"

SV* SPVM_XS_UTIL_new_sv_object(SPVM_ENV* env, SPVM_OBJECT* object, const char* package) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  (void)hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));

  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  (void)hv_store(hv_data, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  HV* hv_class = gv_stashpv(package, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

SPVM_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = (HV*)SvRV(sv_data);
    
    SV** sv_object_ptr = hv_fetch(hv_data, "object", strlen("object"), 0);
    SV* sv_object = sv_object_ptr ? *sv_object_ptr : &PL_sv_undef;
    size_t iv_object = SvIV(SvRV(sv_object));
    SPVM_OBJECT* object = INT2PTR(SPVM_OBJECT*, iv_object);
    
    return object;
  }
  else {
    return NULL;
  }
}

MODULE = SPVM::Data		PACKAGE = SPVM::Data

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);

  assert(SvOK(sv_object));
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(sv_object);

  SV** sv_env_ptr = hv_fetch(hv_object, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  assert(env->ref_count(env, object));
  
  // Decrement reference count
  env->dec_ref_count(env, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Builder		PACKAGE = SPVM::Builder

SV*
compile_spvm(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  SV** sv_package_infos_ptr = hv_fetch(hv_self, "package_infos", strlen("package_infos"), 0);
  SV* sv_package_infos = sv_package_infos_ptr ? *sv_package_infos_ptr : &PL_sv_undef;
  AV* av_package_infos = (AV*)SvRV(sv_package_infos);
  
  int32_t av_package_infos_length = (int32_t)av_len(av_package_infos) + 1;
  
  {
    int32_t i;
    for (i = 0; i < av_package_infos_length; i++) {
      SV** sv_package_info_ptr = av_fetch(av_package_infos, i, 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Name
      SV** sv_name_ptr = hv_fetch(hv_package_info, "name", strlen("name"), 0);
      SV* sv_name = sv_name_ptr ? *sv_name_ptr : &PL_sv_undef;
      const char* name = SvPV_nolen(sv_name);
      
      // File
      SV** sv_file_ptr = hv_fetch(hv_package_info, "file", strlen("file"), 0);
      SV* sv_file = sv_file_ptr ? *sv_file_ptr : &PL_sv_undef;
      const char* file = SvPV_nolen(sv_file);
      
      // Line
      SV** sv_line_ptr = hv_fetch(hv_package_info, "line", strlen("line"), 0);
      SV* sv_line = sv_line_ptr ? *sv_line_ptr : &PL_sv_undef;
      int32_t line = (int32_t)SvIV(sv_line);
      
      // push package to compiler use stack
      SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, name, file, line);
      SPVM_OP* op_type_package = SPVM_OP_build_basic_type(compiler, op_name_package);
      SPVM_OP* op_use_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file, line);
      SPVM_OP_build_use(compiler, op_use_package, op_type_package, NULL, 0);
      SPVM_LIST_push(compiler->op_use_stack, op_use_package);
    }
  }
  
  // Add include paths
  AV* av_include_paths = get_av("main::INC", 0);;
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  {
    int32_t i;
    for (i = 0; i < av_include_paths_length; i++) {
      SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
      SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
      char* include_path = SvPV_nolen(sv_include_path);
      SPVM_LIST_push(compiler->module_include_pathes, include_path);
    }
  }

  // Compile SPVM
  SPVM_COMPILER_compile(compiler);

  SV* sv_compile_success;
  if (compiler->error_count > 0) {
    sv_compile_success = sv_2mortal(newSViv(0));
  }
  else {
    sv_compile_success = sv_2mortal(newSViv(1));
  }
  
  if (compiler->error_count == 0) {
    // Copy package load path to builder
    for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
      const char* package_name = package->name;
      const char* module_file = package->module_file;
      SV* sv_module_file = sv_2mortal(newSVpv(module_file, 0));

      SV** sv_packages_ptr = hv_fetch(hv_self, "packages", strlen("packages"), 0);
      SV* sv_packages = sv_packages_ptr ? *sv_packages_ptr : &PL_sv_undef;
      HV* hv_packages = (HV*)SvRV(sv_packages);
      
      // Create package info hash reference if not exists
      {
        SV** sv_package_info_ptr = hv_fetch(hv_packages, package_name, strlen(package_name), 0);
        if (!sv_package_info_ptr) {
          HV* hv_package_info = (HV*)sv_2mortal((SV*)newHV());
          SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));
          (void)hv_store(hv_packages, package_name, strlen(package_name), SvREFCNT_inc(sv_package_info), 0);
        }
      }
      
      // Package
      SV** sv_package_info_ptr = hv_fetch(hv_packages, package_name, strlen(package_name), 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Package load path
      (void)hv_store(hv_package_info, "module_file", strlen("module_file"), SvREFCNT_inc(sv_module_file), 0);

      // Create subs hash reference if not exists
      {
        SV** sv_subs_ptr = hv_fetch(hv_package_info, "subs", strlen("subs"), 0);
        if (!sv_subs_ptr) {
          HV* hv_subs = (HV*)sv_2mortal((SV*)newHV());
          SV* sv_subs = sv_2mortal(newRV_inc((SV*)hv_subs));
          (void)hv_store(hv_package_info, "subs", strlen("subs"), SvREFCNT_inc(sv_subs), 0);
        }
      }

      // Subroutines
      SV** sv_subs_ptr = hv_fetch(hv_package_info, "subs", strlen("subs"), 0);
      SV* sv_subs = sv_subs_ptr ? *sv_subs_ptr : &PL_sv_undef;
      HV* hv_subs = (HV*)SvRV(sv_subs);
      
      for (int32_t sub_index = 0; sub_index < package->subs->length; sub_index++) {
        SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
        const char* sub_name = sub->name;
        SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, 0));

        // Create sub info hash reference if not exists
        {
          SV** sv_sub_info_ptr = hv_fetch(hv_subs, sub_name, strlen(sub_name), 0);
          if (!sv_sub_info_ptr) {
            HV* hv_sub_info = (HV*)sv_2mortal((SV*)newHV());
            SV* sv_sub_info = sv_2mortal(newRV_inc((SV*)hv_sub_info));
            (void)hv_store(hv_subs, sub_name, strlen(sub_name), SvREFCNT_inc(sv_sub_info), 0);
          }
        }
        SV** sv_sub_info_ptr = hv_fetch(hv_subs, sub_name, strlen(sub_name), 0);
        SV* sv_sub_info = sv_sub_info_ptr ? *sv_sub_info_ptr : &PL_sv_undef;
        HV* hv_sub_info = (HV*)SvRV(sv_sub_info);
        
        // Subroutine have_native_desc
        int32_t sub_have_native_desc = sub->flag & SPVM_SUB_C_FLAG_NATIVE;
        SV* sv_sub_have_native_desc = sv_2mortal(newSViv(sub_have_native_desc));

        // Subroutine have_precompile_desc
        int32_t sub_have_precompile_desc = sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE;
        SV* sv_sub_have_precompile_desc = sv_2mortal(newSViv(sub_have_precompile_desc));

        (void)hv_store(hv_sub_info, "have_native_desc", strlen("have_native_desc"), SvREFCNT_inc(sv_sub_have_native_desc), 0);
        (void)hv_store(hv_sub_info, "have_precompile_desc", strlen("have_precompile_desc"), SvREFCNT_inc(sv_sub_have_precompile_desc), 0);
      }
    }
    
    // Build portable info
    SPVM_PORTABLE* portable = SPVM_PORTABLE_build_portable(compiler);
    
    // Build runtime
    SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_build_runtime(portable);
    
    // Create env
    SPVM_ENV* env = SPVM_RUNTIME_API_create_env(runtime);
    
    // Set ENV
    size_t iv_env = PTR2IV(env);
    SV* sviv_env = sv_2mortal(newSViv(iv_env));
    SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
    (void)hv_store(hv_self, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
  }

  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
call_begin_blocks(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Env
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SPVM_RUNTIME_API_call_begin_blocks(env);
}

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  if (SvOK(sv_env)) {
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    SPVM_RUNTIME* runtime = env->runtime;
    
    SPVM_RUNTIME_API_free_env(env);
    SPVM_RUNTIME_API_free_runtime(runtime);
  }
}

MODULE = SPVM::Builder::CC		PACKAGE = SPVM::Builder::CC

SV*
bind_sub_native(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);
  SV* sv_native_address = ST(3);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
  
  // Set native address to subroutine
  SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
  runtime->sub_cfunc_addresses[sub->id] = native_address;
  
  XSRETURN(0);
}

SV*
build_package_csource_precompile(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];

  int32_t package_id = package->id;
  
  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // Build package csource
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_package_csource(env, string_buffer, package_name);
  
  SV* sv_package_csource = sv_2mortal(newSVpv(string_buffer->buffer + 1, string_buffer->length - 1));
  
  SPVM_STRING_BUFFER_free(string_buffer);

  XPUSHs(sv_package_csource);
  XSRETURN(1);
}

SV*
bind_sub_precompile(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);
  SV* sv_precompile_address = ST(3);
  
  void* sub_precompile_address = INT2PTR(void*, SvIV(sv_precompile_address));
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];

  SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
  runtime->sub_cfunc_addresses[sub->id] = sub_precompile_address;
  
  XSRETURN(0);
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
new_barray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_barray_raw(env, length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int8_t* elems = env->belems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int8_t)SvIV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_barray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_barray);
  XSRETURN(1);
}

SV*
new_barray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length;
  int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_barray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int8_t* elems = env->belems(env, array);
  memcpy(elems, binary, array_length);
  
  // New sv array
  SV* sv_barray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_barray);
  XSRETURN(1);
}

SV*
new_str_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length;
  int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* string = env->new_str_len_raw(env, (char*)binary, array_length);

  // Increment reference count
  env->inc_ref_count(env, string);

  // New sv array
  SV* sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::Data::Array");
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
new_sarray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_sarray_raw(env, length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int16_t* elems = env->selems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int16_t)SvIV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_sarray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_sarray);
  XSRETURN(1);
}

SV*
new_sarray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length / sizeof(int16_t);
  int16_t* binary = (int16_t*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_sarray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int16_t* elems = env->selems(env, array);
  memcpy(elems, binary, array_length * sizeof(int16_t));
  
  // New sv array
  SV* sv_sarray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_sarray);
  XSRETURN(1);
}

SV*
new_iarray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_iarray_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  int32_t* elems = env->ielems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int32_t)SvIV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_iarray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_iarray);
  XSRETURN(1);
}

SV*
new_iarray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length / sizeof(int32_t);
  int32_t* binary = (int32_t*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_iarray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int32_t* elems = env->ielems(env, array);
  memcpy(elems, binary, array_length * sizeof(int32_t));
  
  // New sv array
  SV* sv_iarray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_iarray);
  XSRETURN(1);
}

SV*
new_larray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_larray_raw(env, length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int64_t* elems = env->lelems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int64_t)SvIV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_larray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_larray);
  XSRETURN(1);
}

SV*
new_larray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length / sizeof(int64_t);
  int64_t* binary = (int64_t*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_larray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  int64_t* elems = env->lelems(env, array);
  memcpy(elems, binary, array_length * sizeof(int64_t));
  
  // New sv array
  SV* sv_larray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_larray);
  XSRETURN(1);
}

SV*
new_farray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_farray_raw(env, length);

  // Increment reference count
  env->inc_ref_count(env, array);

  float* elems = env->felems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (float)SvNV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_farray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_farray);
  XSRETURN(1);
}

SV*
new_farray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length / sizeof(float);
  float* binary = (float*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_farray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  float* elems = env->felems(env, array);
  memcpy(elems, binary, array_length * sizeof(float));
  
  // New sv array
  SV* sv_farray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_farray);
  XSRETURN(1);
}

SV*
new_darray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_darray_raw(env, length);

  // Increment reference count
  env->inc_ref_count(env, array);

  double* elems = env->delems(env, array);
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (double)SvNV(sv_value);
    }
  }
  
  // New sv array
  SV* sv_darray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_darray);
  XSRETURN(1);
}

SV*
new_darray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  int32_t binary_length = sv_len(sv_binary);
  int32_t array_length = binary_length / sizeof(double);
  double* binary = (double*)SvPV_nolen(sv_binary);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array = env->new_darray_raw(env, array_length);

  // Increment reference count
  env->inc_ref_count(env, array);

  double* elems = env->delems(env, array);
  memcpy(elems, binary, array_length * sizeof(double));
  
  // New sv array
  SV* sv_darray = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_darray);
  XSRETURN(1);
}

SV*
_new_oarray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Second argument of SPVM::new_oarray must be array reference");
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_oarray_raw(env, basic_type->id, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);

  int32_t array_basic_type_id  = array->basic_type_id;
  int32_t array_type_dimension = array->type_dimension;
  int32_t element_type_dimension = array_type_dimension - 1;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_oelem(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::Data::Package")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_oelem(env, array, index, object);
      }
      else {
        croak("Element is invalid object type");
      }
    }
    else {
      croak("Element must be SPVM::Data object");
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_marray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_element_type_dimension = ST(2);
  SV* sv_elems = ST(3);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  int32_t element_type_dimension = (int32_t)SvIV(sv_element_type_dimension);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_marray_raw(env, basic_type->id, element_type_dimension, length);
  
  int32_t array_basic_type_id = array->basic_type_id;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_oelem(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::Data")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_oelem(env, array, index, object);
      }
      else {
        croak("Element is invalid object type");
      }
    }
    else {
      croak("Element must be inherit SPVM::Data object");
    }
  }
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_varray(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference");
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
    croak("Can't load %s", basic_type_name);
  }
  
  // New array
  void* array = env->new_varray_raw(env, basic_type->id, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;

    if (sv_derived_from(sv_element, "HASH")) {
      
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
      assert(package);
      
      SPVM_RUNTIME_FIELD* first_field = &runtime->fields[package->fields_base];
      assert(first_field);

      void* elems = (void*)env->ielems(env, array);
      
      HV* hv_value = (HV*)SvRV(sv_element);
      int32_t fields_length = package->fields_length;
      // Field exists check
      int32_t hash_keys_length = 0;
      while (hv_iternext(hv_value)) {
        hash_keys_length++;
      }
      if (hash_keys_length != fields_length) {
        croak("Value element hash key is lacked");
      }

      for (int32_t field_index = 0; field_index < package->fields_length; field_index++) {
        SPVM_RUNTIME_FIELD* field = &runtime->fields[package->fields_base + field_index];
        const char* field_name = &runtime->string_pool[field->name_id];
        
        SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
        SV* sv_field_value;
        if (sv_field_value_ptr) {
          sv_field_value = *sv_field_value_ptr;
        }
        else {
          croak("Value element must be defined");
        }

        switch (first_field->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            ((SPVM_VALUE_byte*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_byte)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            ((SPVM_VALUE_short*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_short)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            ((SPVM_VALUE_int*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_int)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            ((SPVM_VALUE_long*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_long)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            ((SPVM_VALUE_float*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_float)SvNV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            ((SPVM_VALUE_double*)elems)[(fields_length * index) + field_index] = (SPVM_VALUE_double)SvNV(sv_field_value);
            break;
          }
          default:
            assert(0);
        }
      }
    }
    else {
      croak("Element must be hash reference");
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_varray_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_binary = ST(2);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined");
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* binary = (void*)SvPV_nolen(sv_binary);
  
  int32_t binary_length = sv_len(sv_binary);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
    croak("Can't load %s", basic_type_name);
  }

  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
  assert(package);
  
  SPVM_RUNTIME_FIELD* first_field = &runtime->fields[package->fields_base];
  assert(first_field);

  int32_t field_length = package->fields_length;

  int32_t array_length;

  switch (first_field->basic_type_id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      array_length = binary_length/ field_length;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      array_length = binary_length / field_length / 2;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      array_length = binary_length / field_length / 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      array_length = binary_length / field_length / 8;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      array_length = binary_length / field_length / 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      array_length = binary_length / field_length / 8;
      break;
    }
    default:
      assert(0);
  }

  SPVM_OBJECT* array = env->new_varray_raw(env, basic_type->id, array_length);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  
  switch (first_field->basic_type_id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      int8_t* elems = env->belems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      int16_t* elems = env->selems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * 2);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      int32_t* elems = env->ielems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * 4);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      int64_t* elems = env->lelems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * 8);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      float* elems = env->felems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * 4);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      double* elems = env->delems(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * 8);
      }
      break;
    }
    default:
      assert(0);
  }

  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_exception_undef(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));

  env->set_exception(env, NULL);
  
  XSRETURN(0);
}

SV*
memory_blocks_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t memory_blocks_count = env->memory_blocks_count(env);
  SV* sv_memory_blocks_count = sv_2mortal(newSViv(memory_blocks_count));
  
  XPUSHs(sv_memory_blocks_count);
  XSRETURN(1);
}

SV*
call_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);

  int32_t arg_start = 3;

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  const char* package_name = SvPV_nolen(sv_package_name);
  const char* sub_name = SvPV_nolen(sv_sub_name);

  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];

  if (package == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
  if (sub == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  const char* sub_signature = &runtime->string_pool[sub->signature_id];
  int32_t sub_id = env->sub_id(env, package_name, sub_name, sub_signature);
  if (sub_id < 0) {
    croak("Subroutine not found %s %s", package_name, sub_signature);
  }

  SPVM_VALUE stack[SPVM_LIMIT_C_STACK_MAX];
  
  int32_t ref_stack_top = 0;
  SPVM_VALUE ref_stack[SPVM_LIMIT_C_STACK_MAX];

  int32_t ref_stack_ids[SPVM_LIMIT_C_STACK_MAX];
  
  // Arguments
  int32_t args_contain_ref = 0;
  {
    // If class method, first argument is ignored
    if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD) {
      arg_start++;
    }
    
    int32_t arg_index;
    // Check argument count
    if (items - arg_start != sub->arg_ids_length) {
      croak("Argument count is defferent");
    }
    
    int32_t arg_var_id = 0;
    for (arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_ARG* arg = &runtime->args[sub->arg_ids_base + arg_index];

      SV* sv_value = ST(arg_index + arg_start);
      
      switch (arg->runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_BYTE : {
          int8_t value = (int8_t)SvIV(sv_value);
          stack[arg_var_id].bval = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_SHORT : {
          int16_t value = (int16_t)SvIV(sv_value);
          stack[arg_var_id].sval = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_INT : {
          int32_t value = (int32_t)SvIV(sv_value);
          stack[arg_var_id].ival = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_LONG : {
          int64_t value = (int64_t)SvIV(sv_value);
          stack[arg_var_id].lval = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_FLOAT : {
          float value = (float)SvNV(sv_value);
          stack[arg_var_id].fval = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE : {
          double value = (double)SvNV(sv_value);
          stack[arg_var_id].dval = value;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int8_t value = (int8_t)SvIV(sv_field_value);
              stack[arg_var_id + field_index].bval = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int16_t value = (int16_t)SvIV(sv_field_value);
              stack[arg_var_id + field_index].sval = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }

            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int32_t value = (int32_t)SvIV(sv_field_value);
              stack[arg_var_id + field_index].ival = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int64_t value = (int64_t)SvIV(sv_field_value);
              stack[arg_var_id + field_index].lval = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              float value = (float)SvNV(sv_field_value);
              stack[arg_var_id + field_index].fval = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE: {
          if (sv_derived_from(sv_value, "HASH")) {
            HV* hv_value = (HV*)SvRV(sv_value);

            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);

            SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
            assert(arg_first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              double value = (double)SvNV(sv_field_value);
              stack[arg_var_id + field_index].dval = value;
            }
            arg_var_id += arg_package->fields_length;
          }
          else {
            croak("%dth argument must be hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
        case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
        case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
        {
          if (!SvOK(sv_value)) {
            stack[arg_var_id].oval = NULL;
          }
          else {
            if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::Data")) {
              SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
              int32_t arg_basic_type_id = arg->basic_type_id;
              
              if (arg_basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY) {
                if (object->type_dimension == 0) {
                  croak("%dth argument is invalid object type", arg_index);
                }
              }
              else {
                int32_t arg_type_dimension = arg->type_dimension;
                if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
                  croak("%dth argument is invalid object type", arg_index);
                }
              }
              
              stack[arg_var_id].oval = object;
            }
            else {
              croak("%dth argument must be inherit SPVM::Data", arg_index);
            }
          }
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          int8_t value = (int8_t)SvIV(sv_value_deref);
          ref_stack[ref_stack_top].bval = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          int16_t value = (int16_t)SvIV(sv_value_deref);
          ref_stack[ref_stack_top].sval = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_INT: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          int32_t value = (int32_t)SvIV(sv_value_deref);
          ref_stack[ref_stack_top].ival = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          int64_t value = (int64_t)SvIV(sv_value_deref);
          ref_stack[ref_stack_top].lval = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          float value = (float)SvNV(sv_value_deref);
          ref_stack[ref_stack_top].fval = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE: {
          args_contain_ref = 1;
          SV* sv_value_deref = SvRV(sv_value);
          double value = (double)SvNV(sv_value_deref);
          ref_stack[ref_stack_top].dval = value;
          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;
          ref_stack_top++;
          arg_var_id++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int8_t value = (int8_t)SvIV(sv_field_value);
              ((SPVM_VALUE_byte*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);
            
            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                sv_field_value = sv_2mortal(newSViv(0));
              }
              int16_t value = (int16_t)SvIV(sv_field_value);
              ((SPVM_VALUE_short*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);

            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              int32_t value = (int32_t)SvIV(sv_field_value);
              ((SPVM_VALUE_int*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);

            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                sv_field_value = sv_2mortal(newSViv(0));
              }
              int64_t value = (int64_t)SvIV(sv_field_value);
              ((SPVM_VALUE_long*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);

            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              float value = (float)SvNV(sv_field_value);
              ((SPVM_VALUE_float*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE: {
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            args_contain_ref = 1;
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
            int32_t arg_basic_type_id = arg->basic_type_id;
            SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

            SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
            assert(arg_package);
        
            SPVM_RUNTIME_FIELD* first_field = &runtime->fields[arg_package->fields_base];
            assert(first_field);

            int32_t fields_length = arg_package->fields_length;
            // Field exists check
            int32_t hash_keys_length = 0;
            while (hv_iternext(hv_value)) {
              hash_keys_length++;
            }
            if (hash_keys_length != fields_length) {
              croak("Value element hash key is lacked");
            }
            
            for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
              SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
              const char* field_name = &runtime->string_pool[field->name_id];

              SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
              SV* sv_field_value;
              if (sv_field_value_ptr) {
                sv_field_value = *sv_field_value_ptr;
              }
              else {
                croak("Value element must be defined");
              }
              double value = (double)SvNV(sv_field_value);
              ((SPVM_VALUE_double*)&ref_stack[ref_stack_top])[field_index] = value;
            }
            stack[arg_var_id].oval = &ref_stack[ref_stack_top];
            ref_stack_ids[arg_index] = ref_stack_top;
            ref_stack_top += fields_length;
            arg_var_id++;
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  
  // Return
  SV* sv_return_value = NULL;
  int32_t excetpion_flag;
  switch (sub->return_runtime_type) {
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE:
    {
      int32_t sub_return_basic_type_id = sub->return_basic_type_id;
      int32_t sub_return_type_dimension = sub->return_type_dimension;

      excetpion_flag = env->call_sub(env, sub_id, stack);
      
      SPVM_RUNTIME_BASIC_TYPE* sub_return_basic_type = &runtime->basic_types[sub_return_basic_type_id];

      SPVM_RUNTIME_PACKAGE* sub_return_package = &runtime->packages[sub_return_basic_type->package_id];
      assert(sub_return_package);
      
      SPVM_RUNTIME_FIELD* sub_return_first_field = &runtime->fields[sub_return_package->fields_base];
      assert(sub_return_first_field);
      
      HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
      for (int32_t field_index = 0; field_index < sub_return_package->fields_length; field_index++) {
        SPVM_RUNTIME_FIELD* field = &runtime->fields[sub_return_package->fields_base + field_index];
        const char* field_name = &runtime->string_pool[field->name_id];
        
        SV* sv_field_value = NULL;
        switch (sub_return_first_field->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            sv_field_value = sv_2mortal(newSViv(stack[field_index].bval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            sv_field_value = sv_2mortal(newSViv(stack[field_index].sval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            sv_field_value = sv_2mortal(newSViv(stack[field_index].ival));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            sv_field_value = sv_2mortal(newSViv(stack[field_index].lval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            sv_field_value = sv_2mortal(newSVnv(stack[field_index].fval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            sv_field_value = sv_2mortal(newSVnv(stack[field_index].dval));
            break;
          }
          default:
            assert(0);
        }
        
        (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
        sv_return_value = sv_2mortal(newRV_inc((SV*)hv_value));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
    case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
    case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
    case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
    case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
    {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        void* return_value = stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          if (sub->return_type_dimension > 0 || sub->return_basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY) {
            sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::Data::Array");
          }
          else if (sub->return_type_dimension == 0) {
            SPVM_RUNTIME_BASIC_TYPE* sub_return_basic_type = &runtime->basic_types[sub->return_basic_type_id];
            const char* basic_type_name = &runtime->string_pool[sub_return_basic_type->name_id];

            SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
            
            sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, SvPV_nolen(sv_basic_type_name));
          }
          else {
            assert(0);
          }
        }
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_VOID: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_BYTE: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].bval));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_SHORT: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].sval));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_INT: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].ival));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_LONG: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].lval));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_FLOAT: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
      }
      break;
    }
    case SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE: {
      excetpion_flag = env->call_sub(env, sub_id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(stack[0].dval));
      }
      break;
    }
    default:
      assert(0);
  }
  
  if (args_contain_ref) {
    for (int32_t arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SV* sv_value = ST(arg_index + arg_start);
      
      SPVM_RUNTIME_ARG* arg = &runtime->args[sub->arg_ids_base + arg_index];
      int32_t ref_stack_id = ref_stack_ids[arg_index];
      switch (arg->runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].bval);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].sval);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_INT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].ival);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].lval);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_id].fval);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_id].dval);
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_byte*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_short*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_int*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_long*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSVnv(((SPVM_VALUE_float*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
          SPVM_RUNTIME_FIELD* arg_first_field = &runtime->fields[arg_package->fields_base];
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = &runtime->fields[arg_package->fields_base + field_index];
            const char* field_name = &runtime->string_pool[field->name_id];
            SV* sv_field_value = sv_2mortal(newSVnv(((SPVM_VALUE_double*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
      }
    }
  }

  // Exception
  if (excetpion_flag) {
    void* exception = env->exception(env);
    int32_t length = env->len(env, exception);
    const char* exception_bytes = (char*)env->belems(env, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_bytes, length));
    croak("%s\n ", SvPV_nolen(sv_exception));
  }
  // Success
  else {
    int32_t return_count;
    if (sub->return_runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_VOID) {
      return_count = 0;
    }
    else {
      XPUSHs(sv_return_value);
      return_count = 1;
    }
    
    XSRETURN(return_count);
  }
}

SV*
to_elems(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array or SPVM::Data::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object");
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->len(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;

    if (array->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY) {
      
      for (int32_t index = 0; index < length; index++) {
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];
        
        SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
        assert(package);
        
        SPVM_RUNTIME_FIELD* first_field = &runtime->fields[package->fields_base];
        assert(first_field);

        void* elems = (void*)env->ielems(env, array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t field_length = package->fields_length;
        for (int32_t field_index = 0; field_index < package->fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = &runtime->fields[package->fields_base + field_index];
          const char* field_name = &runtime->string_pool[field->name_id];

          SV* sv_field_value;
          switch (first_field->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_VALUE_byte field_value = ((SPVM_VALUE_byte*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_VALUE_short field_value = ((SPVM_VALUE_short*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_VALUE_int field_value = ((SPVM_VALUE_int*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_VALUE_long field_value = ((SPVM_VALUE_long*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_VALUE_float field_value = ((SPVM_VALUE_float*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_VALUE_double field_value = ((SPVM_VALUE_double*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            default:
              assert(0);
          }
          SvREFCNT_inc(sv_field_value);
          (void)hv_store(hv_value, field_name, strlen(field_name), sv_field_value, 0);
        }
        SV* sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else if (array->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY) {
      for (int32_t index = 0; index < length; index++) {
        // Element type id
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];

        // Index
        SPVM_OBJECT* value = env->oelem(env, array, index);
        if (value != NULL) {
          env->inc_ref_count(env, value);
        }
        
        int32_t element_type_is_array_type = element_type_dimension > 0;
        SV* sv_value;
        if (element_type_is_array_type) {
          sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::Data::Array");
        }
        else {
          const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
          SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
          sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_basic_type_name));
        }
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->belems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->selems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->ielems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->lelems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->felems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSVnv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->delems(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSVnv(elems[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array type");
  }

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array object or SPVM::Data::Sgtring
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Data must be SPVM::Data::Array");
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->len(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  SV* sv_bin;
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;

    if (array->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY) {
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
      assert(package);
      
      SPVM_RUNTIME_FIELD* first_field = &runtime->fields[package->fields_base];
      assert(first_field);

      int32_t field_length = package->fields_length;

      switch (first_field->basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->belems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->selems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->ielems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->lelems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->felems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->delems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        default:
          croak("Invalid type");
      }
    }
    else if (array->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY) {
      croak("Objec type is not supported");
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->belems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->selems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->ielems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->lelems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->felems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->delems(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        default:
          croak("Invalid type");
      }
    }
  }
  else {
    croak("Argument must be array type");
  }
  
  XPUSHs(sv_bin);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Exe		PACKAGE = SPVM::Builder::Exe

SV*
build_main_csource(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_PORTABLE* portable = runtime->portable;

  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);

  SPVM_CSOURCE_BUILDER_EXE_build_exe_csource(env, string_buffer, portable, package_name);

  SV* sv_main_csource = sv_2mortal(newSVpv(string_buffer->buffer + 1, string_buffer->length - 1));

  SPVM_STRING_BUFFER_free(string_buffer);
  
  XPUSHs(sv_main_csource);
  XSRETURN(1);
}

MODULE = SPVM		PACKAGE = SPVM

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "spvm_api.h"
#include "spvm_bytecode.h"

SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // SPVM Object header byte size
  const int32_t OBJECT_HEADER_BYTE_SIZE = api->get_object_header_byte_size(api);
  
  // SPVM Object header length offset
  const int32_t OBJECT_HEADER_LENGTH_OFFSET = api->get_object_header_length_offset(api);
  
  // Void type code
  const int32_t VOID_TYPE_CODE = api->get_void_type_code(api);

  // Byte type code
  const int32_t BYTE_TYPE_CODE = api->get_byte_type_code(api);

  // Short type code
  const int32_t SHORT_TYPE_CODE = api->get_short_type_code(api);

  // Int type code
  const int32_t INT_TYPE_CODE = api->get_int_type_code(api);

  // Long type code
  const int32_t LONG_TYPE_CODE = api->get_long_type_code(api);

  // Float type code
  const int32_t FLOAT_TYPE_CODE = api->get_float_type_code(api);

  // Double type code
  const int32_t DOUBLE_TYPE_CODE = api->get_double_type_code(api);

  const int32_t object_my_vars_length = api->get_sub_object_my_vars_length(api, sub_id);
  const int32_t object_my_vars_base = api->get_sub_object_my_vars_base(api, sub_id);

  // Debug
  const int32_t debug = api->is_debug(api) ? 1 : 0;
  
  // Constant pool
  const int32_t* constant_pool = api->get_constant_pool(api);
  
  // Package variables
  SPVM_API_VALUE* package_vars = api->get_package_vars(api);
  
  // Bytecodes
  const int32_t* bytecodes = api->get_bytecodes(api);
  
  int32_t bytecode_index = 0;

  // Args length
  int32_t args_length = api->get_sub_args_length(api, sub_id);
  
  // Lexical varialbe length
  int32_t my_vars_length = api->get_sub_my_vars_length(api, sub_id);
  register int32_t operand_stack_top = -1 + my_vars_length;
  
  // Call_stack_max
  int32_t call_stack_length = my_vars_length + api->get_sub_operand_stack_max(api, sub_id);
 
  // Call stack
  SPVM_API_OBJECT* call_stack_array = api->new_value_array(api, call_stack_length);
  api->inc_ref_count(api, call_stack_array);
  SPVM_API_VALUE* call_stack = api->get_value_array_elements(api, (SPVM_API_OBJECT*)call_stack_array);

  // Catch stack
  int32_t catch_exception_stack[255];
  
  // Catch stack top
  int32_t catch_exception_stack_top = -1;

  register int32_t success;
  int32_t current_line = 0;
  
  // Copy arguments
  memcpy(call_stack, args, args_length * sizeof(SPVM_API_VALUE));
  
  // If arg is object, increment reference count
  if (api->get_sub_object_args_length(api, sub_id)) {
    int32_t object_args_base = api->get_sub_object_args_base(api, sub_id);
    int32_t object_args_length = api->get_sub_object_args_length(api, sub_id);
    {
      int32_t i;
      for (i = 0; i < object_args_length; i++) {
        int32_t arg_index = constant_pool[object_args_base + i];
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[arg_index].object_value;
        if (object != NULL) {
          api->inc_ref_count(api, object);
        }
      }
    }
  }
  
  api->set_exception(api, NULL);
  
  // Call native sub
  if (api->get_sub_is_native(api, sub_id)) {
    int32_t return_type_code = api->get_type_code(api, api->get_sub_return_type_id(api, sub_id));
    
    // Call native subroutine
    if (return_type_code == VOID_TYPE_CODE) {
      void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      (*native_address)(api, (SPVM_API_VALUE*)call_stack);
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_VOID;
    }
    else if (return_type_code == BYTE_TYPE_CODE) {
      int8_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      int8_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].byte_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_BYTE;
    }
    else if (return_type_code == SHORT_TYPE_CODE) {
      int16_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      int16_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      operand_stack_top++;
      call_stack[operand_stack_top].short_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_SHORT;
    }
    else if (return_type_code == INT_TYPE_CODE) {
        
      int32_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      
      int32_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].int_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_INT;
    }
    else if (return_type_code == LONG_TYPE_CODE) {
      int64_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      int64_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      operand_stack_top++;
      call_stack[operand_stack_top].long_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_LONG;
    }
    else if (return_type_code == FLOAT_TYPE_CODE) {
      float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      float return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].float_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT;
    }
    else if (return_type_code == DOUBLE_TYPE_CODE) {
      double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);
      double return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].double_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE;
    }
    else {
      
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = api->get_sub_native_address(api, sub_id);

      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_API_VALUE*)call_stack);
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].object_value = return_value_native;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT;
    }
  }
  // Call normal sub
  else {
    bytecode_index = api->get_sub_bytecode_base(api, sub_id);
  }
  
  while (1) {
    switch (bytecodes[bytecode_index]) {
      case SPVM_BYTECODE_C_CODE_NOP:
        // Not used
        assert(0);
      case SPVM_BYTECODE_C_CODE_REG_IS_UNDEF:
        call_stack[bytecodes[bytecode_index + 1]].int_value = call_stack[bytecodes[bytecode_index + 2]].object_value == NULL;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_IS_NOT_UNDEF:
        call_stack[bytecodes[bytecode_index + 1]].int_value = call_stack[bytecodes[bytecode_index + 2]].object_value != NULL;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value == call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value == call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value == call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value == call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value == call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_DOUBLE:
      
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value == call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_EQ_OBJECT:
      
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].object_value == call_stack[bytecodes[bytecode_index + 3]].object_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value != call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value != call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value != call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value != call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value != call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_DOUBLE:
      
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value != call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NE_OBJECT:
      
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].object_value != call_stack[bytecodes[bytecode_index + 3]].object_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value > call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value > call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value > call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value > call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value > call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GT_DOUBLE:
      
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value > call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value >= call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value >= call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value >= call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value >= call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value >= call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GE_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value >= call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value < call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value < call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value < call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value < call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value < call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LT_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value < call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value <= call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value <= call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value <= call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value <= call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value <= call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LE_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value <= call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value + call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value + call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value + call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value + call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value + call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ADD_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value + call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value - call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value - call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value - call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value - call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value - call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_SUBTRACT_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value - call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value * call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value * call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value * call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value * call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value * call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_MULTIPLY_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value * call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_BYTE:
        if (call_stack[bytecodes[bytecode_index + 3]].byte_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (byte / byte)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[bytecodes[bytecode_index + 1]].byte_value
            = call_stack[bytecodes[bytecode_index + 2]].byte_value / call_stack[bytecodes[bytecode_index + 3]].byte_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_SHORT:
        if (call_stack[bytecodes[bytecode_index + 3]].short_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (short / short)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[bytecodes[bytecode_index + 1]].short_value
            = call_stack[bytecodes[bytecode_index + 2]].short_value / call_stack[bytecodes[bytecode_index + 3]].short_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_INT:
        if (call_stack[bytecodes[bytecode_index + 3]].int_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (int / int)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[bytecodes[bytecode_index + 1]].int_value
            = call_stack[bytecodes[bytecode_index + 2]].int_value / call_stack[bytecodes[bytecode_index + 3]].int_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_LONG:
        if (call_stack[bytecodes[bytecode_index + 3]].long_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (long / long)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[bytecodes[bytecode_index + 1]].long_value
            = call_stack[bytecodes[bytecode_index + 2]].long_value / call_stack[bytecodes[bytecode_index + 3]].long_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value
          = call_stack[bytecodes[bytecode_index + 2]].float_value / call_stack[bytecodes[bytecode_index + 3]].float_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_DIVIDE_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value
          = call_stack[bytecodes[bytecode_index + 2]].double_value / call_stack[bytecodes[bytecode_index + 3]].double_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value % call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value % call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value % call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value % call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value
          = (float)fmod((double)call_stack[bytecodes[bytecode_index + 2]].float_value, call_stack[bytecodes[bytecode_index + 3]].float_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_REMAINDER_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value
          = fmod(call_stack[bytecodes[bytecode_index + 2]].double_value, call_stack[bytecodes[bytecode_index + 3]].double_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value << call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value << call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value << call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value << call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value >> call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value >> call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value >> call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value >> call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = (int8_t)((uint8_t)call_stack[bytecodes[bytecode_index + 2]].byte_value >> call_stack[bytecodes[bytecode_index + 3]].byte_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = (int16_t)((uint16_t)call_stack[bytecodes[bytecode_index + 2]].short_value >> call_stack[bytecodes[bytecode_index + 3]].short_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = (int32_t)((uint32_t)call_stack[bytecodes[bytecode_index + 2]].int_value >> call_stack[bytecodes[bytecode_index + 3]].int_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = (int64_t)((uint64_t)call_stack[bytecodes[bytecode_index + 2]].long_value >> call_stack[bytecodes[bytecode_index + 3]].long_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_AND_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value & call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_AND_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value & call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_AND_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value & call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_AND_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value & call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_OR_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value | call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_OR_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value | call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_OR_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value | call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_OR_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value | call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_XOR_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value
          = call_stack[bytecodes[bytecode_index + 2]].byte_value ^ call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_XOR_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value
          = call_stack[bytecodes[bytecode_index + 2]].short_value ^ call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_XOR_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value
          = call_stack[bytecodes[bytecode_index + 2]].int_value ^ call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BIT_XOR_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value
          = call_stack[bytecodes[bytecode_index + 2]].long_value ^ call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = -call_stack[bytecodes[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = -call_stack[bytecodes[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = -call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = -call_stack[bytecodes[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = -call_stack[bytecodes[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_NEGATE_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = -call_stack[bytecodes[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_LONG:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_BOOL_OBJECT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = !!call_stack[bytecodes[bytecode_index + 2]].object_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_INC_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value += (int8_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_INC_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value += (int16_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_INC_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value += (int32_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_INC_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value += (int64_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LOAD_CONSTANT:
        memcpy(&call_stack[bytecodes[bytecode_index + 1]], &constant_pool[bytecodes[bytecode_index + 2]], sizeof(int32_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LOAD_CONSTANT2:
        memcpy(&call_stack[bytecodes[bytecode_index + 1]], &constant_pool[bytecodes[bytecode_index + 2]], sizeof(int64_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = (int64_t)call_stack[bytecodes[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = (float)call_stack[bytecodes[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = (double)call_stack[bytecodes[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = (int32_t)call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = (float)call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = (double)call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = (int32_t)call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = (int64_t)call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = (double)call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = (int32_t)call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = (int64_t)call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = (float)call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = (int8_t)(call_stack[bytecodes[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = (int16_t)(call_stack[bytecodes[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = (int32_t)call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = (int32_t)call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = (int64_t)call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = (float)call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = (double)call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = (int8_t)call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = (int64_t)call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = (float)call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = (double)call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = (int8_t)call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = (int16_t)call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = (int8_t)call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = (int16_t)call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = (int8_t)call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = (int16_t)call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = (int16_t)call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value = call_stack[bytecodes[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value = call_stack[bytecodes[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value = call_stack[bytecodes[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value = call_stack[bytecodes[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_FLOAT:
        call_stack[bytecodes[bytecode_index + 1]].float_value = call_stack[bytecodes[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_DOUBLE:
        call_stack[bytecodes[bytecode_index + 1]].double_value = call_stack[bytecodes[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      
      /* TODO */
      case SPVM_BYTECODE_C_CODE_REG_UNDEF:
        call_stack[bytecodes[bytecode_index + 1]].object_value = NULL;
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_REG_LOAD:
        call_stack[bytecodes[bytecode_index + 1]] = call_stack[bytecodes[bytecode_index + 2]];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecode_index + 1].byte_value
              = *(int8_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 1]].short_value
              = *(int16_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 3]].int_value = *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 1]].long_value = *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 1]].float_value = *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 1]].double_value = *(double*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            call_stack[bytecodes[bytecode_index + 1]] = *(SPVM_API_VALUE*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(int8_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = call_stack[bytecodes[bytecode_index + 3]].byte_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(int16_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = call_stack[bytecodes[bytecode_index + 3]].short_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = call_stack[bytecodes[bytecode_index + 3]].int_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = call_stack[bytecodes[bytecode_index + 3]].long_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = call_stack[bytecodes[bytecode_index + 3]].float_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            *(double*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = call_stack[bytecodes[bytecode_index + 3]].double_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t index = call_stack[bytecodes[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
          }
          else {
            SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            
            // Decrement old object reference count
            if (*object_address != NULL) {
              api->dec_ref_count(api, *object_address);
            }
            
            // Store address
            *object_address = call_stack[bytecodes[bytecode_index + 3]].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              api->inc_ref_count(api, *object_address);
            }
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_STORE:
        call_stack[bytecodes[bytecode_index + 1]] = call_stack[bytecodes[bytecode_index + 2]];
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_REG_STORE_OBJECT: {
        // Decrement reference count
        if (call_stack[bytecodes[bytecode_index + 1]].object_value != NULL) {
          api->dec_ref_count(api, call_stack[bytecodes[bytecode_index + 1]].object_value);
        }
        
        // Store object
        call_stack[bytecodes[bytecode_index + 1]].object_value = call_stack[bytecodes[bytecode_index + 2]].object_value;
        
        // Increment new value reference count
        if (call_stack[bytecodes[bytecode_index + 1]].object_value != NULL) {
          api->inc_ref_count(api, call_stack[bytecodes[bytecode_index + 1]].object_value);
        }
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = bytecodes[bytecode_index + 2];
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        call_stack[bytecodes[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_INT_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set array
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = bytecodes[bytecode_index + 1];
        
        // length
        int32_t length = call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        // Set object
        call_stack[bytecodes[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_NEW_STRING: {
        int32_t name_id = bytecodes[bytecode_index + 2];
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&constant_pool[name_id + 1], constant_pool[name_id]);

        // Set string
        call_stack[bytecodes[bytecode_index + 1]].object_value = string;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_ARRAY_LENGTH:
        if (call_stack[bytecodes[bytecode_index + 2]].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          call_stack[bytecodes[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)call_stack[bytecodes[bytecode_index + 2]].object_value + OBJECT_HEADER_LENGTH_OFFSET);
          bytecode_index += 3;
          break;
        }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        int8_t value = api->get_byte_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].byte_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        int16_t value = api->get_short_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].short_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        int32_t value = api->get_int_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].int_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        int64_t value = api->get_long_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].long_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        float value = api->get_float_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].float_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        double value = api->get_double_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].double_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 3];

        SPVM_API_OBJECT* value = api->get_object_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_WEAKEN_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        
        api->weaken_object_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        int8_t value = call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        api->set_byte_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        int16_t value = call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        api->set_short_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        int32_t value = call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        api->set_int_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        int64_t value = call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        api->set_long_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        float value = call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        api->set_float_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        double value = call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        api->set_double_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value;
        int32_t field_id = bytecodes[bytecode_index + 2];
        SPVM_API_OBJECT* value = call_stack[bytecodes[bytecode_index + 3]].object_value;
        
        api->set_object_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_STRING: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        SPVM_API_OBJECT* string2 = call_stack[bytecodes[bytecode_index + 3]].object_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_string(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_BYTE: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        int8_t string2 = call_stack[bytecodes[bytecode_index + 3]].byte_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_byte(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_SHORT: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        int16_t string2 = call_stack[bytecodes[bytecode_index + 3]].short_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_short(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_INT: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        int32_t string2 = call_stack[bytecodes[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_int(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_LONG: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        int64_t string2 = call_stack[bytecodes[bytecode_index + 3]].long_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_long(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_FLOAT: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        float string2 = call_stack[bytecodes[bytecode_index + 3]].float_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_float(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_DOUBLE: {
        SPVM_API_OBJECT* string1 = call_stack[bytecodes[bytecode_index + 2]].object_value;
        double string2 = call_stack[bytecodes[bytecode_index + 3]].double_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_double(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        
        call_stack[bytecodes[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_LOAD_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 2];
        
        call_stack[bytecodes[bytecode_index + 1]] = package_vars[package_var_id];
        
        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_STORE_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];

        package_vars[package_var_id] = call_stack[bytecodes[bytecode_index + 2]];

        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];
        
        // Decrement reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->dec_ref_count(api, package_vars[package_var_id].object_value);
        }
        
        // Store object
        package_vars[package_var_id].object_value = call_stack[bytecodes[bytecode_index + 2]].object_value;
        
        // Increment new value reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->inc_ref_count(api, package_vars[package_var_id].object_value);
        }

        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_PUSH_CATCH_EXCEPTION: {
        // Next operation
        int16_t jump_offset_abs = bytecodes[bytecode_index + 1];
        
        catch_exception_stack_top++;
        catch_exception_stack[catch_exception_stack_top] = jump_offset_abs;
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_POP_CATCH_EXCEPTION: {
        catch_exception_stack_top--;
        
        bytecode_index++;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_LOAD_EXCEPTION: {
        call_stack[bytecodes[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)api->get_exception(api);
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_STORE_EXCEPTION: {
        
        api->set_exception(api, (SPVM_API_OBJECT*)call_stack[bytecodes[bytecode_index + 1]].object_value);
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_CURRENT_LINE:
        current_line = bytecodes[bytecode_index + 1];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_REG_CALL_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = bytecodes[bytecode_index + 2];
        
        int32_t args_length = api->get_sub_args_length(api, call_sub_id);
        
        operand_stack_top -= args_length;
        
        SPVM_API_VALUE args[255];
        memcpy(args, &call_stack[operand_stack_top + 1], sizeof(SPVM_API_VALUE) * args_length);
        
        // Call subroutine
        SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_REG_CROAK;
        }
        else {
          if (!api->get_sub_is_void(api, call_sub_id)) {
            call_stack[bytecodes[bytecode_index + 1]] = return_value;
          }
          
          // Next operation
          bytecode_index += 3 + (debug * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_RETURN_BYTE:
      case SPVM_BYTECODE_C_CODE_REG_RETURN_SHORT:
      case SPVM_BYTECODE_C_CODE_REG_RETURN_INT:
      case SPVM_BYTECODE_C_CODE_REG_RETURN_LONG:
      case SPVM_BYTECODE_C_CODE_REG_RETURN_FLOAT:
      case SPVM_BYTECODE_C_CODE_REG_RETURN_DOUBLE:
      {
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_BYTE:
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_SHORT:
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_INT:
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_LONG:
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_FLOAT:
        label_SPVM_BYTECODE_C_CODE_REG_RETURN_DOUBLE:
        {
        
          // Get return value
          SPVM_API_VALUE return_value = call_stack[bytecodes[bytecode_index + 1]];
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_RETURN_OBJECT: {

        label_SPVM_BYTECODE_C_CODE_REG_RETURN_OBJECT: {
        
          SPVM_API_VALUE return_value = call_stack[bytecodes[bytecode_index + 1]];
          
          // Increment ref count of return value not to release by decrement
          if (return_value.object_value != NULL) {
            api->inc_ref_count(api, return_value.object_value);
          }
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }

          // Decrement ref count of return value
          if (return_value.object_value != NULL) {
            api->dec_ref_count_only(api, return_value.object_value);
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_RETURN_VOID: {

        label_SPVM_BYTECODE_C_CODE_REG_RETURN_VOID: {

          SPVM_API_VALUE return_value;
          memset(&return_value, 0, sizeof(SPVM_API_VALUE));
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);

          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_REG_CROAK: {
        
        label_SPVM_BYTECODE_C_CODE_REG_CROAK:
        
        // Catch exception
        if (catch_exception_stack_top > -1) {
          
          int32_t jump_offset_abs = catch_exception_stack[catch_exception_stack_top];
          catch_exception_stack_top--;
          
          bytecode_index = api->get_sub_bytecode_base(api, sub_id) + jump_offset_abs;
          
          break;
        }
        
        // Decrement object my vars reference count
        if (object_my_vars_length) {
          {
            int32_t i;
            for (i = 0; i < object_my_vars_length; i++) {
              int32_t my_var_index = constant_pool[object_my_vars_base + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        // Sub name
        int32_t sub_name_id = api->get_sub_name_id(api, sub_id);
        const char* sub_name = (char*)&constant_pool[sub_name_id + 1];
        
        // File name
        int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
        const char* file_name = (char*)&constant_pool[file_name_id + 1];
        
        // stack trace strings
        const char* from = "\n  from ";
        const char* at = "() at ";

        // Exception
        SPVM_API_OBJECT* exception = api->get_exception(api);
        char* exception_chars = api->get_string_chars(api, exception);
        int32_t exception_length = api->get_string_length(api, exception);
        
        // Total string length
        int32_t total_length = 0;
        total_length += exception_length;
        total_length += strlen(from);
        total_length += strlen(sub_name);
        total_length += strlen(at);
        total_length += strlen(file_name);

        const char* line = " line ";
        char line_str[20];
        
        if (debug) {
          sprintf(line_str, "%" PRId32, current_line);
          total_length += strlen(line);
          total_length += strlen(line_str);
        }
        
        // Create exception message
        SPVM_API_OBJECT* new_exception = api->new_string(api, NULL, total_length);
        char* new_exception_chars = api->get_string_chars(api, new_exception);
        
        memcpy(
          (void*)(new_exception_chars),
          (void*)(exception_chars),
          exception_length
        );
        if (debug) {
          sprintf(
            new_exception_chars + exception_length,
            "%s%s%s%s%s%" PRId32,
            from,
            sub_name,
            at,
            file_name,
            line,
            current_line
          );
        }
        else {
          sprintf(
            new_exception_chars + exception_length,
            "%s%s%s%s",
            from,
            sub_name,
            at,
            file_name
          );
        }
        
        // Set exception
        api->set_exception(api, new_exception);
        
        SPVM_API_VALUE return_value;
        
        memset(&return_value, 0, sizeof(SPVM_API_VALUE));
        
        api->dec_ref_count(api, call_stack_array);
        
        return return_value;
      }
      case SPVM_BYTECODE_C_CODE_REG_POP:
        operand_stack_top--;
        bytecode_index++;
        break;
      case SPVM_BYTECODE_C_CODE_REG_IF_EQ_ZERO:
        success = call_stack[operand_stack_top].int_value == 0;
        bytecode_index += success * bytecodes[bytecode_index + 1] + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_REG_IF_NE_ZERO:
        success = call_stack[operand_stack_top].int_value != 0;
        bytecode_index += success * bytecodes[bytecode_index + 1] + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_REG_GOTO:
        bytecode_index += bytecodes[bytecode_index + 1];
        break;
      case SPVM_BYTECODE_C_CODE_REG_TABLE_SWITCH: {
        // default offset
        int32_t default_offset = bytecodes[bytecode_index + 1];
        
        // min
        int32_t min = bytecodes[bytecode_index + 2];
        
        // max
        int32_t max = bytecodes[bytecode_index + 3];
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&bytecodes[bytecode_index + 4]) + (call_stack[operand_stack_top].int_value - min));
          bytecode_index += branch_offset;
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_LOOKUP_SWITCH: {

        /*
        1  default
        5  npare
        9  match  13 branch // min
        17 match 21 branch
        25 match 29 branch // max
        */
        
        // default offset
        int32_t default_offset = bytecodes[bytecode_index + 1];
        
        // npare
        int32_t pair_count = bytecodes[bytecode_index + 2];
        
        // min
        int32_t min = bytecodes[bytecode_index + 3];
        
        // max
        int32_t max = bytecodes[bytecode_index + 3 + (pair_count - 1) * 2];
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              bytecode_index += default_offset;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = bytecodes[bytecode_index + 3 + (cur_half_pos * 2)];
            
            if (call_stack[operand_stack_top].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (call_stack[operand_stack_top].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = bytecodes[bytecode_index + 3 + (cur_half_pos * 2) + 1];
              bytecode_index += branch_offset;
              break;
            }
          }
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_REG_PUSH_ARG:
        operand_stack_top++;
        call_stack[operand_stack_top] = call_stack[bytecodes[bytecode_index + 1]];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_REG_POP_ARGS:
        operand_stack_top -= bytecodes[bytecode_index + 1];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_UNDEF:
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (void*)NULL;
        bytecode_index++;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD:
        operand_stack_top++;
        call_stack[operand_stack_top] = call_stack[bytecodes[bytecode_index + 1]];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].byte_value
              = *(int8_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].short_value
              = *(int16_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1] = *(SPVM_API_VALUE*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            operand_stack_top--;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].byte_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].short_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = call_stack[operand_stack_top].float_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(double*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].double_value;
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            
            // Decrement old object reference count
            if (*object_address != NULL) {
              api->dec_ref_count(api, *object_address);
            }
            
            // Store address
            *object_address = call_stack[operand_stack_top].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              api->inc_ref_count(api, *object_address);
            }
            
            operand_stack_top -= 3;
            bytecode_index++;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_STORE:
        call_stack[bytecodes[bytecode_index + 1]] = call_stack[operand_stack_top];
        operand_stack_top--;
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_STORE_OBJECT: {
        int32_t index = bytecodes[bytecode_index + 1];
        
        // Decrement reference count
        if (call_stack[index].object_value != NULL) {
          api->dec_ref_count(api, call_stack[index].object_value);
        }
        
        // Store object
        call_stack[index].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (call_stack[index].object_value != NULL) {
          api->inc_ref_count(api, call_stack[index].object_value);
        }
        
        operand_stack_top--;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = bytecodes[bytecode_index + 1];
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (SPVM_API_OBJECT*)object;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = bytecodes[bytecode_index + 1];
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set object
        call_stack[operand_stack_top].object_value = object;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_STRING: {
        int32_t name_id = bytecodes[bytecode_index + 1];
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&constant_pool[name_id + 1], constant_pool[name_id]);

        // Set string
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = string;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
        if (call_stack[operand_stack_top].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top].int_value = *(int32_t*)((intptr_t)call_stack[operand_stack_top].object_value + OBJECT_HEADER_LENGTH_OFFSET);
          bytecode_index++;
          break;
        }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        int8_t value = api->get_byte_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].byte_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        int16_t value = api->get_short_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].short_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        int32_t value = api->get_int_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].int_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        int64_t value = api->get_long_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].long_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        float value = api->get_float_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].float_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        double value = api->get_double_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].double_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];

        SPVM_API_OBJECT* value = api->get_object_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top].object_value = value;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->weaken_object_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int8_t value = call_stack[operand_stack_top].byte_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_byte_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int16_t value = call_stack[operand_stack_top].short_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_short_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t value = call_stack[operand_stack_top].int_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_int_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int64_t value = call_stack[operand_stack_top].long_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_long_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        float value = call_stack[operand_stack_top].float_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_float_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        double value = call_stack[operand_stack_top].double_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_double_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        SPVM_API_OBJECT* value = call_stack[operand_stack_top].object_value;
        int32_t field_id = bytecodes[bytecode_index + 1];
        
        api->set_object_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        operand_stack_top -= 2;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        SPVM_API_OBJECT* string2 = call_stack[operand_stack_top].object_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_string(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int8_t string2 = call_stack[operand_stack_top].byte_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_byte(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int16_t string2 = call_stack[operand_stack_top].short_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_short(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int32_t string2 = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_int(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int64_t string2 = call_stack[operand_stack_top].long_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_long(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        float string2 = call_stack[operand_stack_top].float_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_float(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        double string2 = call_stack[operand_stack_top].double_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_double(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];
        
        operand_stack_top++;
        call_stack[operand_stack_top] = package_vars[package_var_id];
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];

        package_vars[package_var_id] = call_stack[operand_stack_top];
        operand_stack_top--;

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];
        
        // Decrement reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->dec_ref_count(api, package_vars[package_var_id].object_value);
        }
        
        // Store object
        package_vars[package_var_id].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->inc_ref_count(api, package_vars[package_var_id].object_value);
        }
        
        operand_stack_top--;

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_PUSH_CATCH_EXCEPTION: {
        // Next operation
        int16_t jump_offset_abs = bytecodes[bytecode_index + 1];
        
        catch_exception_stack_top++;
        catch_exception_stack[catch_exception_stack_top] = jump_offset_abs;
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_POP_CATCH_EXCEPTION: {
        catch_exception_stack_top--;
        
        bytecode_index++;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION: {
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (SPVM_API_OBJECT*)api->get_exception(api);
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_EXCEPTION: {
        
        api->set_exception(api, (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value);
        
        operand_stack_top--;
        
        bytecode_index++;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CURRENT_LINE:
        current_line = bytecodes[bytecode_index + 1];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_CALL_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = bytecodes[bytecode_index + 1];
        
        int32_t args_length = api->get_sub_args_length(api, call_sub_id);
        
        operand_stack_top -= args_length;
        
        SPVM_API_VALUE args[255];
        memcpy(args, &call_stack[operand_stack_top + 1], sizeof(SPVM_API_VALUE) * args_length);
        
        // Call subroutine
        SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (!api->get_sub_is_void(api, call_sub_id)) {
            operand_stack_top++;
            call_stack[operand_stack_top] = return_value;
          }
          
          // Next operation
          bytecode_index += 2 + (debug * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_BYTE:
      case SPVM_BYTECODE_C_CODE_RETURN_SHORT:
      case SPVM_BYTECODE_C_CODE_RETURN_INT:
      case SPVM_BYTECODE_C_CODE_RETURN_LONG:
      case SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
      case SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
      {
        label_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
        label_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
        label_SPVM_BYTECODE_C_CODE_RETURN_INT:
        label_SPVM_BYTECODE_C_CODE_RETURN_LONG:
        label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
        label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
        {
        
          // Get return value
          SPVM_API_VALUE return_value = call_stack[operand_stack_top];
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {

        label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
        
          SPVM_API_VALUE return_value = call_stack[operand_stack_top];
          
          // Increment ref count of return value not to release by decrement
          if (return_value.object_value != NULL) {
            api->inc_ref_count(api, return_value.object_value);
          }
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }

          // Decrement ref count of return value
          if (return_value.object_value != NULL) {
            api->dec_ref_count_only(api, return_value.object_value);
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_VOID: {

        label_SPVM_BYTECODE_C_CODE_RETURN_VOID: {

          SPVM_API_VALUE return_value;
          memset(&return_value, 0, sizeof(SPVM_API_VALUE));
          
          // Decrement object my vars reference count
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);

          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_CROAK: {
        
        label_SPVM_BYTECODE_C_CODE_CROAK:
        
        // Catch exception
        if (catch_exception_stack_top > -1) {
          
          int32_t jump_offset_abs = catch_exception_stack[catch_exception_stack_top];
          catch_exception_stack_top--;
          
          bytecode_index = api->get_sub_bytecode_base(api, sub_id) + jump_offset_abs;
          
          break;
        }
        
        // Decrement object my vars reference count
        if (object_my_vars_length) {
          {
            int32_t i;
            for (i = 0; i < object_my_vars_length; i++) {
              int32_t my_var_index = constant_pool[object_my_vars_base + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        // Sub name
        int32_t sub_name_id = api->get_sub_name_id(api, sub_id);
        const char* sub_name = (char*)&constant_pool[sub_name_id + 1];
        
        // File name
        int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
        const char* file_name = (char*)&constant_pool[file_name_id + 1];
        
        // stack trace strings
        const char* from = "\n  from ";
        const char* at = "() at ";

        // Exception
        SPVM_API_OBJECT* exception = api->get_exception(api);
        char* exception_chars = api->get_string_chars(api, exception);
        int32_t exception_length = api->get_string_length(api, exception);
        
        // Total string length
        int32_t total_length = 0;
        total_length += exception_length;
        total_length += strlen(from);
        total_length += strlen(sub_name);
        total_length += strlen(at);
        total_length += strlen(file_name);

        const char* line = " line ";
        char line_str[20];
        
        if (debug) {
          sprintf(line_str, "%" PRId32, current_line);
          total_length += strlen(line);
          total_length += strlen(line_str);
        }
        
        // Create exception message
        SPVM_API_OBJECT* new_exception = api->new_string(api, NULL, total_length);
        char* new_exception_chars = api->get_string_chars(api, new_exception);
        
        memcpy(
          (void*)(new_exception_chars),
          (void*)(exception_chars),
          exception_length
        );
        if (debug) {
          sprintf(
            new_exception_chars + exception_length,
            "%s%s%s%s%s%" PRId32,
            from,
            sub_name,
            at,
            file_name,
            line,
            current_line
          );
        }
        else {
          sprintf(
            new_exception_chars + exception_length,
            "%s%s%s%s",
            from,
            sub_name,
            at,
            file_name
          );
        }
        
        // Set exception
        api->set_exception(api, new_exception);
        
        SPVM_API_VALUE return_value;
        
        memset(&return_value, 0, sizeof(SPVM_API_VALUE));
        
        api->dec_ref_count(api, call_stack_array);
        
        return return_value;
      }
      case SPVM_BYTECODE_C_CODE_POP:
        operand_stack_top--;
        bytecode_index++;
        break;
      case SPVM_BYTECODE_C_CODE_IF_EQ_ZERO:
        success = call_stack[operand_stack_top].int_value == 0;
        bytecode_index += success * bytecodes[bytecode_index + 1] + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_NE_ZERO:
        success = call_stack[operand_stack_top].int_value != 0;
        bytecode_index += success * bytecodes[bytecode_index + 1] + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_GOTO:
        bytecode_index += bytecodes[bytecode_index + 1];
        break;
      case SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
        // default offset
        int32_t default_offset = bytecodes[bytecode_index + 1];
        
        // min
        int32_t min = bytecodes[bytecode_index + 2];
        
        // max
        int32_t max = bytecodes[bytecode_index + 3];
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&bytecodes[bytecode_index + 4]) + (call_stack[operand_stack_top].int_value - min));
          bytecode_index += branch_offset;
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH: {

        /*
        1  default
        5  npare
        9  match  13 branch // min
        17 match 21 branch
        25 match 29 branch // max
        */
        
        // default offset
        int32_t default_offset = bytecodes[bytecode_index + 1];
        
        // npare
        int32_t pair_count = bytecodes[bytecode_index + 2];
        
        // min
        int32_t min = bytecodes[bytecode_index + 3];
        
        // max
        int32_t max = bytecodes[bytecode_index + 3 + (pair_count - 1) * 2];
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              bytecode_index += default_offset;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = bytecodes[bytecode_index + 3 + (cur_half_pos * 2)];
            
            if (call_stack[operand_stack_top].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (call_stack[operand_stack_top].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = bytecodes[bytecode_index + 3 + (cur_half_pos * 2) + 1];
              bytecode_index += branch_offset;
              break;
            }
          }
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
    }
  }
}

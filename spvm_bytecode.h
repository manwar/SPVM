#ifndef SPVM_BYTECODE_H
#define SPVM_BYTECODE_H

#include "spvm_base.h"






























































































enum {
  SPVM_BYTECODE_C_CODE_REG_NOP,
  SPVM_BYTECODE_C_CODE_UNDEF,
  SPVM_BYTECODE_C_CODE_LOAD,
  SPVM_BYTECODE_C_CODE_STORE,
  SPVM_BYTECODE_C_CODE_STORE_OBJECT,
  SPVM_BYTECODE_C_CODE_POP,
  SPVM_BYTECODE_C_CODE_NEW_OBJECT,
  SPVM_BYTECODE_C_CODE_NEW_STRING,
  SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY,
  SPVM_BYTECODE_C_CODE_TABLE_SWITCH,
  SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH,
  SPVM_BYTECODE_C_CODE_CALL_SUB,
  SPVM_BYTECODE_C_CODE_CROAK,
  SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY,
  SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY,
  SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY,
  SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY,
  SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY,
  SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT,
  SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_ADD_BYTE,
  SPVM_BYTECODE_C_CODE_REG_ADD_SHORT,
  SPVM_BYTECODE_C_CODE_REG_ADD_INT,
  SPVM_BYTECODE_C_CODE_REG_ADD_LONG,
  SPVM_BYTECODE_C_CODE_REG_ADD_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_ADD_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_INT,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_LONG,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_SUBTRACT_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_BYTE,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_SHORT,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_INT,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_LONG,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_MULTIPLY_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_INT,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_LONG,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_DIVIDE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_BYTE,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_SHORT,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_INT,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_LONG,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_REMAINDER_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_INT,
  SPVM_BYTECODE_C_CODE_REG_LEFT_SHIFT_LONG,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_INT,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_LONG,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_BYTE,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_SHORT,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_INT,
  SPVM_BYTECODE_C_CODE_REG_RIGHT_SHIFT_UNSIGNED_LONG,
  SPVM_BYTECODE_C_CODE_REG_BIT_AND_BYTE,
  SPVM_BYTECODE_C_CODE_REG_BIT_AND_SHORT,
  SPVM_BYTECODE_C_CODE_REG_BIT_AND_INT,
  SPVM_BYTECODE_C_CODE_REG_BIT_AND_LONG,
  SPVM_BYTECODE_C_CODE_REG_BIT_OR_BYTE,
  SPVM_BYTECODE_C_CODE_REG_BIT_OR_SHORT,
  SPVM_BYTECODE_C_CODE_REG_BIT_OR_INT,
  SPVM_BYTECODE_C_CODE_REG_BIT_OR_LONG,
  SPVM_BYTECODE_C_CODE_REG_BIT_XOR_BYTE,
  SPVM_BYTECODE_C_CODE_REG_BIT_XOR_SHORT,
  SPVM_BYTECODE_C_CODE_REG_BIT_XOR_INT,
  SPVM_BYTECODE_C_CODE_REG_BIT_XOR_LONG,
  SPVM_BYTECODE_C_CODE_REG_COMPLEMENT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_COMPLEMENT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_COMPLEMENT_INT,
  SPVM_BYTECODE_C_CODE_REG_COMPLEMENT_LONG,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_INT,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_LONG,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_NEGATE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_BYTE_TO_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_SHORT_TO_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_INT_TO_INT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_LONG_TO_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_FLOAT_TO_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONVERT_DOUBLE_TO_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_LOAD_CONSTANT,
  SPVM_BYTECODE_C_CODE_REG_LOAD_CONSTANT2,
  SPVM_BYTECODE_C_CODE_REG_GT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_GT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_GT_INT,
  SPVM_BYTECODE_C_CODE_REG_GT_LONG,
  SPVM_BYTECODE_C_CODE_REG_GT_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_GT_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_GE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_GE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_GE_INT,
  SPVM_BYTECODE_C_CODE_REG_GE_LONG,
  SPVM_BYTECODE_C_CODE_REG_GE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_GE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_LT_BYTE,
  SPVM_BYTECODE_C_CODE_REG_LT_SHORT,
  SPVM_BYTECODE_C_CODE_REG_LT_INT,
  SPVM_BYTECODE_C_CODE_REG_LT_LONG,
  SPVM_BYTECODE_C_CODE_REG_LT_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_LT_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_LE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_LE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_LE_INT,
  SPVM_BYTECODE_C_CODE_REG_LE_LONG,
  SPVM_BYTECODE_C_CODE_REG_LE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_LE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_IS_UNDEF,
  SPVM_BYTECODE_C_CODE_REG_IS_NOT_UNDEF,
  SPVM_BYTECODE_C_CODE_REG_EQ_BYTE,
  SPVM_BYTECODE_C_CODE_REG_EQ_SHORT,
  SPVM_BYTECODE_C_CODE_REG_EQ_INT,
  SPVM_BYTECODE_C_CODE_REG_EQ_LONG,
  SPVM_BYTECODE_C_CODE_REG_EQ_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_EQ_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_EQ_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_NE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_NE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_NE_INT,
  SPVM_BYTECODE_C_CODE_REG_NE_LONG,
  SPVM_BYTECODE_C_CODE_REG_NE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_NE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_NE_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_INC_BYTE,
  SPVM_BYTECODE_C_CODE_REG_INC_SHORT,
  SPVM_BYTECODE_C_CODE_REG_INC_INT,
  SPVM_BYTECODE_C_CODE_REG_INC_LONG,
  SPVM_BYTECODE_C_CODE_REG_BOOL_BYTE,
  SPVM_BYTECODE_C_CODE_REG_BOOL_SHORT,
  SPVM_BYTECODE_C_CODE_REG_BOOL_INT,
  SPVM_BYTECODE_C_CODE_REG_BOOL_LONG,
  SPVM_BYTECODE_C_CODE_REG_BOOL_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_BOOL_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_BOOL_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_UNDEF,
  SPVM_BYTECODE_C_CODE_REG_LOAD,
  SPVM_BYTECODE_C_CODE_REG_STORE,
  SPVM_BYTECODE_C_CODE_REG_STORE_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_POP,
  SPVM_BYTECODE_C_CODE_REG_NEW_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_NEW_STRING,
  SPVM_BYTECODE_C_CODE_REG_NEW_OBJECT_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_BYTE,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_SHORT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_INT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_LONG,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LOAD_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_BYTE,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_SHORT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_INT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_LONG,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_STORE_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_ARRAY_LENGTH,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_BYTE,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_SHORT,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_INT,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_LONG,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_GET_FIELD_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_BYTE,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_SHORT,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_INT,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_LONG,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_SET_FIELD_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_IF_EQ_ZERO,
  SPVM_BYTECODE_C_CODE_REG_IF_NE_ZERO,
  SPVM_BYTECODE_C_CODE_REG_TABLE_SWITCH,
  SPVM_BYTECODE_C_CODE_REG_LOOKUP_SWITCH,
  SPVM_BYTECODE_C_CODE_REG_GOTO,
  SPVM_BYTECODE_C_CODE_REG_CALL_SUB,
  SPVM_BYTECODE_C_CODE_REG_RETURN_VOID,
  SPVM_BYTECODE_C_CODE_REG_RETURN_BYTE,
  SPVM_BYTECODE_C_CODE_REG_RETURN_SHORT,
  SPVM_BYTECODE_C_CODE_REG_RETURN_INT,
  SPVM_BYTECODE_C_CODE_REG_RETURN_LONG,
  SPVM_BYTECODE_C_CODE_REG_RETURN_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_RETURN_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_RETURN_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_CROAK,
  SPVM_BYTECODE_C_CODE_REG_LOAD_EXCEPTION_VAR,
  SPVM_BYTECODE_C_CODE_REG_STORE_EXCEPTION_VAR,
  SPVM_BYTECODE_C_CODE_REG_CURRENT_LINE,
  SPVM_BYTECODE_C_CODE_REG_WEAKEN_FIELD_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_NEW_BYTE_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_NEW_SHORT_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_NEW_INT_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_NEW_LONG_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_NEW_FLOAT_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_NEW_DOUBLE_ARRAY,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_STRING,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_BYTE,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_SHORT,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_INT,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_LONG,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_FLOAT,
  SPVM_BYTECODE_C_CODE_REG_CONCAT_STRING_DOUBLE,
  SPVM_BYTECODE_C_CODE_REG_PUSH_CATCH_EXCEPTION,
  SPVM_BYTECODE_C_CODE_REG_POP_CATCH_EXCEPTION,
  SPVM_BYTECODE_C_CODE_REG_LOAD_PACKAGE_VAR,
  SPVM_BYTECODE_C_CODE_REG_LOAD_PACKAGE_VAR_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_STORE_PACKAGE_VAR,
  SPVM_BYTECODE_C_CODE_REG_STORE_PACKAGE_VAR_OBJECT,
  SPVM_BYTECODE_C_CODE_REG_PUSH_ARG,
  SPVM_BYTECODE_C_CODE_REG_POP_ARGS,
};

extern const char* const SPVM_BYTECODE_C_CODE_NAMES[];

#endif

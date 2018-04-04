#ifndef SPVM_OPCODE_H
#define SPVM_OPCODE_H

#include "spvm_base.h"






























































































enum {
  SPVM_OPCODE_C_ID_NOP,
  SPVM_OPCODE_C_ID_ADD_INT,
  SPVM_OPCODE_C_ID_ADD_LONG,
  SPVM_OPCODE_C_ID_ADD_FLOAT,
  SPVM_OPCODE_C_ID_ADD_DOUBLE,
  SPVM_OPCODE_C_ID_SUBTRACT_INT,
  SPVM_OPCODE_C_ID_SUBTRACT_LONG,
  SPVM_OPCODE_C_ID_SUBTRACT_FLOAT,
  SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE,
  SPVM_OPCODE_C_ID_MULTIPLY_INT,
  SPVM_OPCODE_C_ID_MULTIPLY_LONG,
  SPVM_OPCODE_C_ID_MULTIPLY_FLOAT,
  SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE,
  SPVM_OPCODE_C_ID_DIVIDE_INT,
  SPVM_OPCODE_C_ID_DIVIDE_LONG,
  SPVM_OPCODE_C_ID_DIVIDE_FLOAT,
  SPVM_OPCODE_C_ID_DIVIDE_DOUBLE,
  SPVM_OPCODE_C_ID_REMAINDER_INT,
  SPVM_OPCODE_C_ID_REMAINDER_LONG,
  SPVM_OPCODE_C_ID_REMAINDER_FLOAT,
  SPVM_OPCODE_C_ID_REMAINDER_DOUBLE,
  SPVM_OPCODE_C_ID_LEFT_SHIFT_INT,
  SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG,
  SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT,
  SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG,
  SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT,
  SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG,
  SPVM_OPCODE_C_ID_BIT_AND_INT,
  SPVM_OPCODE_C_ID_BIT_AND_LONG,
  SPVM_OPCODE_C_ID_BIT_OR_INT,
  SPVM_OPCODE_C_ID_BIT_OR_LONG,
  SPVM_OPCODE_C_ID_BIT_XOR_INT,
  SPVM_OPCODE_C_ID_BIT_XOR_LONG,
  SPVM_OPCODE_C_ID_COMPLEMENT_INT,
  SPVM_OPCODE_C_ID_COMPLEMENT_LONG,
  SPVM_OPCODE_C_ID_PLUS_INT,
  SPVM_OPCODE_C_ID_PLUS_LONG,
  SPVM_OPCODE_C_ID_PLUS_FLOAT,
  SPVM_OPCODE_C_ID_PLUS_DOUBLE,
  SPVM_OPCODE_C_ID_NEGATE_INT,
  SPVM_OPCODE_C_ID_NEGATE_LONG,
  SPVM_OPCODE_C_ID_NEGATE_FLOAT,
  SPVM_OPCODE_C_ID_NEGATE_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE,
  SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING,
  SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING,
  SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING,
  SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING,
  SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING,
  SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING,
  SPVM_OPCODE_C_ID_GT_INT,
  SPVM_OPCODE_C_ID_GT_LONG,
  SPVM_OPCODE_C_ID_GT_FLOAT,
  SPVM_OPCODE_C_ID_GT_DOUBLE,
  SPVM_OPCODE_C_ID_GE_INT,
  SPVM_OPCODE_C_ID_GE_LONG,
  SPVM_OPCODE_C_ID_GE_FLOAT,
  SPVM_OPCODE_C_ID_GE_DOUBLE,
  SPVM_OPCODE_C_ID_LT_INT,
  SPVM_OPCODE_C_ID_LT_LONG,
  SPVM_OPCODE_C_ID_LT_FLOAT,
  SPVM_OPCODE_C_ID_LT_DOUBLE,
  SPVM_OPCODE_C_ID_LE_INT,
  SPVM_OPCODE_C_ID_LE_LONG,
  SPVM_OPCODE_C_ID_LE_FLOAT,
  SPVM_OPCODE_C_ID_LE_DOUBLE,
  SPVM_OPCODE_C_ID_IS_UNDEF,
  SPVM_OPCODE_C_ID_IS_NOT_UNDEF,
  SPVM_OPCODE_C_ID_EQ_INT,
  SPVM_OPCODE_C_ID_EQ_LONG,
  SPVM_OPCODE_C_ID_EQ_FLOAT,
  SPVM_OPCODE_C_ID_EQ_DOUBLE,
  SPVM_OPCODE_C_ID_EQ_OBJECT,
  SPVM_OPCODE_C_ID_NE_INT,
  SPVM_OPCODE_C_ID_NE_LONG,
  SPVM_OPCODE_C_ID_NE_FLOAT,
  SPVM_OPCODE_C_ID_NE_DOUBLE,
  SPVM_OPCODE_C_ID_NE_OBJECT,
  SPVM_OPCODE_C_ID_INC_BYTE,
  SPVM_OPCODE_C_ID_INC_SHORT,
  SPVM_OPCODE_C_ID_INC_INT,
  SPVM_OPCODE_C_ID_INC_LONG,
  SPVM_OPCODE_C_ID_INC_FLOAT,
  SPVM_OPCODE_C_ID_INC_DOUBLE,
  SPVM_OPCODE_C_ID_BOOL_INT,
  SPVM_OPCODE_C_ID_BOOL_LONG,
  SPVM_OPCODE_C_ID_BOOL_FLOAT,
  SPVM_OPCODE_C_ID_BOOL_DOUBLE,
  SPVM_OPCODE_C_ID_BOOL_OBJECT,
  SPVM_OPCODE_C_ID_LOAD_UNDEF,
  SPVM_OPCODE_C_ID_NEW_OBJECT,
  SPVM_OPCODE_C_ID_NEW_STRING,
  SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_BYTE,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_SHORT,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_INT,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_LONG,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_FLOAT,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_DOUBLE,
  SPVM_OPCODE_C_ID_ARRAY_LOAD_OBJECT,
  SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE,
  SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT,
  SPVM_OPCODE_C_ID_ARRAY_STORE_INT,
  SPVM_OPCODE_C_ID_ARRAY_STORE_LONG,
  SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT,
  SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE,
  SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT,
  SPVM_OPCODE_C_ID_ARRAY_LENGTH,
  SPVM_OPCODE_C_ID_GET_FIELD_BYTE,
  SPVM_OPCODE_C_ID_GET_FIELD_SHORT,
  SPVM_OPCODE_C_ID_GET_FIELD_INT,
  SPVM_OPCODE_C_ID_GET_FIELD_LONG,
  SPVM_OPCODE_C_ID_GET_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_GET_FIELD_OBJECT,
  SPVM_OPCODE_C_ID_SET_FIELD_BYTE,
  SPVM_OPCODE_C_ID_SET_FIELD_SHORT,
  SPVM_OPCODE_C_ID_SET_FIELD_INT,
  SPVM_OPCODE_C_ID_SET_FIELD_LONG,
  SPVM_OPCODE_C_ID_SET_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_SET_FIELD_OBJECT,
  SPVM_OPCODE_C_ID_IF_EQ_ZERO,
  SPVM_OPCODE_C_ID_IF_NE_ZERO,
  SPVM_OPCODE_C_ID_TABLE_SWITCH,
  SPVM_OPCODE_C_ID_TABLE_SWITCH_RANGE,
  SPVM_OPCODE_C_ID_LOOKUP_SWITCH,
  SPVM_OPCODE_C_ID_GOTO,
  SPVM_OPCODE_C_ID_CALL_SUB,
  SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD,
  SPVM_OPCODE_C_ID_RETURN,
  SPVM_OPCODE_C_ID_CROAK,
  SPVM_OPCODE_C_ID_LOAD_EXCEPTION_VAR,
  SPVM_OPCODE_C_ID_STORE_EXCEPTION_VAR,
  SPVM_OPCODE_C_ID_CURRENT_LINE,
  SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT,
  SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY,
  SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_INT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_LONG_ARRAY,
  SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY,
  SPVM_OPCODE_C_ID_CONCAT_STRING_STRING,
  SPVM_OPCODE_C_ID_CONCAT_STRING_BYTE,
  SPVM_OPCODE_C_ID_CONCAT_STRING_SHORT,
  SPVM_OPCODE_C_ID_CONCAT_STRING_INT,
  SPVM_OPCODE_C_ID_CONCAT_STRING_LONG,
  SPVM_OPCODE_C_ID_CONCAT_STRING_FLOAT,
  SPVM_OPCODE_C_ID_CONCAT_STRING_DOUBLE,
  SPVM_OPCODE_C_ID_PUSH_EVAL,
  SPVM_OPCODE_C_ID_POP_EVAL,
  SPVM_OPCODE_C_ID_PUSH_ARG,
  SPVM_OPCODE_C_ID_INC_REF_COUNT,
  SPVM_OPCODE_C_ID_DEC_REF_COUNT,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_BYTE,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_SHORT,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_INT,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_LONG,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_FLOAT,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_DOUBLE,
  SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_OBJECT,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_BYTE,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_SHORT,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_INT,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_LONG,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_FLOAT,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_DOUBLE,
  SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_OBJECT,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_BYTE,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_SHORT,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_INT,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_LONG,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_FLOAT,
  SPVM_OPCODE_C_ID_LOAD_CONSTANT_DOUBLE,
  SPVM_OPCODE_C_ID_CASE,
  SPVM_OPCODE_C_ID_IF_CROAK_CATCH,
  SPVM_OPCODE_C_ID_IF_CROAK_RETURN,
  SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE,
  SPVM_OPCODE_C_ID_MOVE_BYTE,
  SPVM_OPCODE_C_ID_MOVE_SHORT,
  SPVM_OPCODE_C_ID_MOVE_INT,
  SPVM_OPCODE_C_ID_MOVE_LONG,
  SPVM_OPCODE_C_ID_MOVE_FLOAT,
  SPVM_OPCODE_C_ID_MOVE_DOUBLE,
  SPVM_OPCODE_C_ID_MOVE_OBJECT,
  SPVM_OPCODE_C_ID_PUSH_OBJECT_VAR_INDEX,
  SPVM_OPCODE_C_ID_ENTER_SCOPE,
  SPVM_OPCODE_C_ID_LEAVE_SCOPE,
  SPVM_OPCODE_C_ID_END,
  SPVM_OPCODE_C_ID_PUSH_ARG_BYTE,
  SPVM_OPCODE_C_ID_PUSH_ARG_SHORT,
  SPVM_OPCODE_C_ID_PUSH_ARG_INT,
  SPVM_OPCODE_C_ID_PUSH_ARG_LONG,
  SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT,
  SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE,
  SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT,
  SPVM_OPCODE_C_ID_CHECK_CAST,
};

enum {
  SPVM_OPCODE_C_FLAG_IS_LABEL = 1
};

extern const char* const SPVM_OPCODE_C_ID_NAMES[];

struct SPVM_opcode {
  uint16_t id;
  int32_t operand0;
  int32_t operand1;
  int32_t operand2;
};

enum {
  SPVM_OPCODE_C_UNIT = sizeof(SPVM_OPCODE) / sizeof(int32_t)
};

SPVM_OPCODE* SPVM_OPCODE_new();

#endif

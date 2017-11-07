#include "spvm_bytecode.h"

































































































const char* const SPVM_BYTECODE_C_CODE_NAMES[] = {
  "NOP",
  "UNDEF",
  "LOAD",
  "STORE",
  "STORE_OBJECT",
  "POP",
  "NEW_OBJECT",
  "NEW_STRING",
  "NEW_OBJECT_ARRAY",
  "ARRAY_LOAD_BYTE",
  "ARRAY_LOAD_SHORT",
  "ARRAY_LOAD_INT",
  "ARRAY_LOAD_LONG",
  "ARRAY_LOAD_FLOAT",
  "ARRAY_LOAD_DOUBLE",
  "ARRAY_LOAD_OBJECT",
  "ARRAY_STORE_BYTE",
  "ARRAY_STORE_SHORT",
  "ARRAY_STORE_INT",
  "ARRAY_STORE_LONG",
  "ARRAY_STORE_FLOAT",
  "ARRAY_STORE_DOUBLE",
  "ARRAY_STORE_OBJECT",
  "ARRAY_LENGTH",
  "GET_FIELD_BYTE",
  "GET_FIELD_SHORT",
  "GET_FIELD_INT",
  "GET_FIELD_LONG",
  "GET_FIELD_FLOAT",
  "GET_FIELD_DOUBLE",
  "GET_FIELD_OBJECT",
  "SET_FIELD_BYTE",
  "SET_FIELD_SHORT",
  "SET_FIELD_INT",
  "SET_FIELD_LONG",
  "SET_FIELD_FLOAT",
  "SET_FIELD_DOUBLE",
  "SET_FIELD_OBJECT",
  "IF_EQ_ZERO",
  "IF_NE_ZERO",
  "TABLE_SWITCH",
  "LOOKUP_SWITCH",
  "GOTO",
  "CALL_SUB",
  "RETURN_VOID",
  "RETURN_BYTE",
  "RETURN_SHORT",
  "RETURN_INT",
  "RETURN_LONG",
  "RETURN_FLOAT",
  "RETURN_DOUBLE",
  "RETURN_OBJECT",
  "CROAK",
  "LOAD_EXCEPTION",
  "STORE_EXCEPTION",
  "CURRENT_LINE",
  "WEAKEN_FIELD",
  "NEW_BYTE_ARRAY",
  "NEW_SHORT_ARRAY",
  "NEW_INT_ARRAY",
  "NEW_LONG_ARRAY",
  "NEW_FLOAT_ARRAY",
  "NEW_DOUBLE_ARRAY",
  "CONCAT_STRING_STRING",
  "CONCAT_STRING_BYTE",
  "CONCAT_STRING_SHORT",
  "CONCAT_STRING_INT",
  "CONCAT_STRING_LONG",
  "CONCAT_STRING_FLOAT",
  "CONCAT_STRING_DOUBLE",
  "PUSH_CATCH_EXCEPTION",
  "POP_CATCH_EXCEPTION",
  "LOAD_PACKAGE_VAR",
  "STORE_PACKAGE_VAR",
  "STORE_PACKAGE_VAR_OBJECT",
  "REG_ADD_BYTE",
  "REG_ADD_SHORT",
  "REG_ADD_INT",
  "REG_ADD_LONG",
  "REG_ADD_FLOAT",
  "REG_ADD_DOUBLE",
  "REG_SUBTRACT_BYTE",
  "REG_SUBTRACT_SHORT",
  "REG_SUBTRACT_INT",
  "REG_SUBTRACT_LONG",
  "REG_SUBTRACT_FLOAT",
  "REG_SUBTRACT_DOUBLE",
  "REG_MULTIPLY_BYTE",
  "REG_MULTIPLY_SHORT",
  "REG_MULTIPLY_INT",
  "REG_MULTIPLY_LONG",
  "REG_MULTIPLY_FLOAT",
  "REG_MULTIPLY_DOUBLE",
  "REG_DIVIDE_BYTE",
  "REG_DIVIDE_SHORT",
  "REG_DIVIDE_INT",
  "REG_DIVIDE_LONG",
  "REG_DIVIDE_FLOAT",
  "REG_DIVIDE_DOUBLE",
  "REG_REMAINDER_BYTE",
  "REG_REMAINDER_SHORT",
  "REG_REMAINDER_INT",
  "REG_REMAINDER_LONG",
  "REG_REMAINDER_FLOAT",
  "REG_REMAINDER_DOUBLE",
  "REG_LEFT_SHIFT_BYTE",
  "REG_LEFT_SHIFT_SHORT",
  "REG_LEFT_SHIFT_INT",
  "REG_LEFT_SHIFT_LONG",
  "REG_RIGHT_SHIFT_BYTE",
  "REG_RIGHT_SHIFT_SHORT",
  "REG_RIGHT_SHIFT_INT",
  "REG_RIGHT_SHIFT_LONG",
  "REG_RIGHT_SHIFT_UNSIGNED_BYTE",
  "REG_RIGHT_SHIFT_UNSIGNED_SHORT",
  "REG_RIGHT_SHIFT_UNSIGNED_INT",
  "REG_RIGHT_SHIFT_UNSIGNED_LONG",
  "REG_BIT_AND_BYTE",
  "REG_BIT_AND_SHORT",
  "REG_BIT_AND_INT",
  "REG_BIT_AND_LONG",
  "REG_BIT_OR_BYTE",
  "REG_BIT_OR_SHORT",
  "REG_BIT_OR_INT",
  "REG_BIT_OR_LONG",
  "REG_BIT_XOR_BYTE",
  "REG_BIT_XOR_SHORT",
  "REG_BIT_XOR_INT",
  "REG_BIT_XOR_LONG",
  "REG_NEGATE_BYTE",
  "REG_NEGATE_SHORT",
  "REG_NEGATE_INT",
  "REG_NEGATE_LONG",
  "REG_NEGATE_FLOAT",
  "REG_NEGATE_DOUBLE",
  "REG_CONVERT_BYTE_TO_SHORT",
  "REG_CONVERT_BYTE_TO_INT",
  "REG_CONVERT_BYTE_TO_LONG",
  "REG_CONVERT_BYTE_TO_FLOAT",
  "REG_CONVERT_BYTE_TO_DOUBLE",
  "REG_CONVERT_SHORT_TO_BYTE",
  "REG_CONVERT_SHORT_TO_INT",
  "REG_CONVERT_SHORT_TO_LONG",
  "REG_CONVERT_SHORT_TO_FLOAT",
  "REG_CONVERT_SHORT_TO_DOUBLE",
  "REG_CONVERT_INT_TO_BYTE",
  "REG_CONVERT_INT_TO_SHORT",
  "REG_CONVERT_INT_TO_LONG",
  "REG_CONVERT_INT_TO_FLOAT",
  "REG_CONVERT_INT_TO_DOUBLE",
  "REG_CONVERT_LONG_TO_BYTE",
  "REG_CONVERT_LONG_TO_SHORT",
  "REG_CONVERT_LONG_TO_INT",
  "REG_CONVERT_LONG_TO_FLOAT",
  "REG_CONVERT_LONG_TO_DOUBLE",
  "REG_CONVERT_FLOAT_TO_BYTE",
  "REG_CONVERT_FLOAT_TO_SHORT",
  "REG_CONVERT_FLOAT_TO_INT",
  "REG_CONVERT_FLOAT_TO_LONG",
  "REG_CONVERT_FLOAT_TO_DOUBLE",
  "REG_CONVERT_DOUBLE_TO_BYTE",
  "REG_CONVERT_DOUBLE_TO_SHORT",
  "REG_CONVERT_DOUBLE_TO_INT",
  "REG_CONVERT_DOUBLE_TO_LONG",
  "REG_CONVERT_DOUBLE_TO_FLOAT",
  "REG_CONVERT_BYTE_TO_BYTE",
  "REG_CONVERT_SHORT_TO_SHORT",
  "REG_CONVERT_INT_TO_INT",
  "REG_CONVERT_LONG_TO_LONG",
  "REG_CONVERT_FLOAT_TO_FLOAT",
  "REG_CONVERT_DOUBLE_TO_DOUBLE",
  "REG_LOAD_CONSTANT",
  "REG_LOAD_CONSTANT2",
  "REG_GT_BYTE",
  "REG_GT_SHORT",
  "REG_GT_INT",
  "REG_GT_LONG",
  "REG_GT_FLOAT",
  "REG_GT_DOUBLE",
  "REG_GE_BYTE",
  "REG_GE_SHORT",
  "REG_GE_INT",
  "REG_GE_LONG",
  "REG_GE_FLOAT",
  "REG_GE_DOUBLE",
  "REG_LT_BYTE",
  "REG_LT_SHORT",
  "REG_LT_INT",
  "REG_LT_LONG",
  "REG_LT_FLOAT",
  "REG_LT_DOUBLE",
  "REG_LE_BYTE",
  "REG_LE_SHORT",
  "REG_LE_INT",
  "REG_LE_LONG",
  "REG_LE_FLOAT",
  "REG_LE_DOUBLE",
  "REG_IS_UNDEF",
  "REG_IS_NOT_UNDEF",
  "REG_EQ_BYTE",
  "REG_EQ_SHORT",
  "REG_EQ_INT",
  "REG_EQ_LONG",
  "REG_EQ_FLOAT",
  "REG_EQ_DOUBLE",
  "REG_EQ_OBJECT",
  "REG_NE_BYTE",
  "REG_NE_SHORT",
  "REG_NE_INT",
  "REG_NE_LONG",
  "REG_NE_FLOAT",
  "REG_NE_DOUBLE",
  "REG_NE_OBJECT",
  "REG_INC_BYTE",
  "REG_INC_SHORT",
  "REG_INC_INT",
  "REG_INC_LONG",
  "REG_BOOL_BYTE",
  "REG_BOOL_SHORT",
  "REG_BOOL_INT",
  "REG_BOOL_LONG",
  "REG_BOOL_FLOAT",
  "REG_BOOL_DOUBLE",
  "REG_BOOL_OBJECT",
  "REG_NOP",
  "REG_UNDEF",
  "REG_LOAD",
  "REG_STORE",
  "REG_STORE_OBJECT",
  "REG_POP",
  "REG_NEW_OBJECT",
  "REG_NEW_STRING",
  "REG_NEW_OBJECT_ARRAY",
  "REG_ARRAY_LOAD_BYTE",
  "REG_ARRAY_LOAD_SHORT",
  "REG_ARRAY_LOAD_INT",
  "REG_ARRAY_LOAD_LONG",
  "REG_ARRAY_LOAD_FLOAT",
  "REG_ARRAY_LOAD_DOUBLE",
  "REG_ARRAY_LOAD_OBJECT",
  "REG_ARRAY_STORE_BYTE",
  "REG_ARRAY_STORE_SHORT",
  "REG_ARRAY_STORE_INT",
  "REG_ARRAY_STORE_LONG",
  "REG_ARRAY_STORE_FLOAT",
  "REG_ARRAY_STORE_DOUBLE",
  "REG_ARRAY_STORE_OBJECT",
  "REG_ARRAY_LENGTH",
  "REG_GET_FIELD_BYTE",
  "REG_GET_FIELD_SHORT",
  "REG_GET_FIELD_INT",
  "REG_GET_FIELD_LONG",
  "REG_GET_FIELD_FLOAT",
  "REG_GET_FIELD_DOUBLE",
  "REG_GET_FIELD_OBJECT",
  "REG_SET_FIELD_BYTE",
  "REG_SET_FIELD_SHORT",
  "REG_SET_FIELD_INT",
  "REG_SET_FIELD_LONG",
  "REG_SET_FIELD_FLOAT",
  "REG_SET_FIELD_DOUBLE",
  "REG_SET_FIELD_OBJECT",
  "REG_IF_EQ_ZERO",
  "REG_IF_NE_ZERO",
  "REG_TABLE_SWITCH",
  "REG_LOOKUP_SWITCH",
  "REG_GOTO",
  "REG_CALL_SUB",
  "REG_RETURN_VOID",
  "REG_RETURN_BYTE",
  "REG_RETURN_SHORT",
  "REG_RETURN_INT",
  "REG_RETURN_LONG",
  "REG_RETURN_FLOAT",
  "REG_RETURN_DOUBLE",
  "REG_RETURN_OBJECT",
  "REG_CROAK",
  "REG_LOAD_EXCEPTION",
  "REG_STORE_EXCEPTION",
  "REG_CURRENT_LINE",
  "REG_WEAKEN_FIELD",
  "REG_NEW_BYTE_ARRAY",
  "REG_NEW_SHORT_ARRAY",
  "REG_NEW_INT_ARRAY",
  "REG_NEW_LONG_ARRAY",
  "REG_NEW_FLOAT_ARRAY",
  "REG_NEW_DOUBLE_ARRAY",
  "REG_CONCAT_STRING_STRING",
  "REG_CONCAT_STRING_BYTE",
  "REG_CONCAT_STRING_SHORT",
  "REG_CONCAT_STRING_INT",
  "REG_CONCAT_STRING_LONG",
  "REG_CONCAT_STRING_FLOAT",
  "REG_CONCAT_STRING_DOUBLE",
  "REG_PUSH_CATCH_EXCEPTION",
  "REG_POP_CATCH_EXCEPTION",
  "REG_LOAD_PACKAGE_VAR",
  "REG_STORE_PACKAGE_VAR",
  "REG_STORE_PACKAGE_VAR_OBJECT",
};

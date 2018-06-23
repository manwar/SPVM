#include "spvm_opcode.h"
#include "spvm_compiler.h"
#include "spvm_compiler_allocator.h"































































































const char* const SPVM_OPCODE_C_ID_NAMES[] = {
  "ADD_INT",
  "ADD_LONG",
  "ADD_FLOAT",
  "ADD_DOUBLE",
  "SUBTRACT_INT",
  "SUBTRACT_LONG",
  "SUBTRACT_FLOAT",
  "SUBTRACT_DOUBLE",
  "MULTIPLY_INT",
  "MULTIPLY_LONG",
  "MULTIPLY_FLOAT",
  "MULTIPLY_DOUBLE",
  "DIVIDE_INT",
  "DIVIDE_LONG",
  "DIVIDE_FLOAT",
  "DIVIDE_DOUBLE",
  "REMAINDER_INT",
  "REMAINDER_LONG",
  "REMAINDER_FLOAT",
  "REMAINDER_DOUBLE",
  "LEFT_SHIFT_INT",
  "LEFT_SHIFT_LONG",
  "RIGHT_SHIFT_INT",
  "RIGHT_SHIFT_LONG",
  "RIGHT_SHIFT_UNSIGNED_INT",
  "RIGHT_SHIFT_UNSIGNED_LONG",
  "BIT_AND_INT",
  "BIT_AND_LONG",
  "BIT_OR_INT",
  "BIT_OR_LONG",
  "BIT_XOR_INT",
  "BIT_XOR_LONG",
  "COMPLEMENT_INT",
  "COMPLEMENT_LONG",
  "NEGATE_INT",
  "NEGATE_LONG",
  "NEGATE_FLOAT",
  "NEGATE_DOUBLE",
  "CONVERT_BYTE_TO_SHORT",
  "CONVERT_BYTE_TO_INT",
  "CONVERT_BYTE_TO_LONG",
  "CONVERT_BYTE_TO_FLOAT",
  "CONVERT_BYTE_TO_DOUBLE",
  "CONVERT_SHORT_TO_BYTE",
  "CONVERT_SHORT_TO_INT",
  "CONVERT_SHORT_TO_LONG",
  "CONVERT_SHORT_TO_FLOAT",
  "CONVERT_SHORT_TO_DOUBLE",
  "CONVERT_INT_TO_BYTE",
  "CONVERT_INT_TO_SHORT",
  "CONVERT_INT_TO_LONG",
  "CONVERT_INT_TO_FLOAT",
  "CONVERT_INT_TO_DOUBLE",
  "CONVERT_LONG_TO_BYTE",
  "CONVERT_LONG_TO_SHORT",
  "CONVERT_LONG_TO_INT",
  "CONVERT_LONG_TO_FLOAT",
  "CONVERT_LONG_TO_DOUBLE",
  "CONVERT_FLOAT_TO_BYTE",
  "CONVERT_FLOAT_TO_SHORT",
  "CONVERT_FLOAT_TO_INT",
  "CONVERT_FLOAT_TO_LONG",
  "CONVERT_FLOAT_TO_DOUBLE",
  "CONVERT_DOUBLE_TO_BYTE",
  "CONVERT_DOUBLE_TO_SHORT",
  "CONVERT_DOUBLE_TO_INT",
  "CONVERT_DOUBLE_TO_LONG",
  "CONVERT_DOUBLE_TO_FLOAT",
  "CONVERT_BYTE_TO_BYTE",
  "CONVERT_SHORT_TO_SHORT",
  "CONVERT_INT_TO_INT",
  "CONVERT_LONG_TO_LONG",
  "CONVERT_FLOAT_TO_FLOAT",
  "CONVERT_DOUBLE_TO_DOUBLE",
  "CONVERT_BYTE_TO_STRING",
  "CONVERT_SHORT_TO_STRING",
  "CONVERT_INT_TO_STRING",
  "CONVERT_LONG_TO_STRING",
  "CONVERT_FLOAT_TO_STRING",
  "CONVERT_DOUBLE_TO_STRING",
  "CONVERT_BYTE_ARRAY_TO_STRING_ARRAY",
  "CONVERT_SHORT_ARRAY_TO_STRING_ARRAY",
  "CONVERT_INT_ARRAY_TO_STRING_ARRAY",
  "CONVERT_LONG_ARRAY_TO_STRING_ARRAY",
  "CONVERT_FLOAT_ARRAY_TO_STRING_ARRAY",
  "CONVERT_DOUBLE_ARRAY_TO_STRING_ARRAY",
  "GT_INT",
  "GT_LONG",
  "GT_FLOAT",
  "GT_DOUBLE",
  "GE_INT",
  "GE_LONG",
  "GE_FLOAT",
  "GE_DOUBLE",
  "LT_INT",
  "LT_LONG",
  "LT_FLOAT",
  "LT_DOUBLE",
  "LE_INT",
  "LE_LONG",
  "LE_FLOAT",
  "LE_DOUBLE",
  "IS_UNDEF",
  "IS_NOT_UNDEF",
  "EQ_INT",
  "EQ_LONG",
  "EQ_FLOAT",
  "EQ_DOUBLE",
  "EQ_OBJECT",
  "NE_INT",
  "NE_LONG",
  "NE_FLOAT",
  "NE_DOUBLE",
  "NE_OBJECT",
  "INC_BYTE",
  "INC_SHORT",
  "INC_INT",
  "INC_LONG",
  "INC_FLOAT",
  "INC_DOUBLE",
  "BOOL_INT",
  "BOOL_LONG",
  "BOOL_FLOAT",
  "BOOL_DOUBLE",
  "BOOL_OBJECT",
  "NEW_OBJECT",
  "NEW_STRING",
  "NEW_OBJECT_ARRAY",
  "NEW_MULTI_ARRAY",
  "ARRAY_FETCH_BYTE",
  "ARRAY_FETCH_SHORT",
  "ARRAY_FETCH_INT",
  "ARRAY_FETCH_LONG",
  "ARRAY_FETCH_FLOAT",
  "ARRAY_FETCH_DOUBLE",
  "ARRAY_FETCH_OBJECT",
  "ARRAY_STORE_BYTE",
  "ARRAY_STORE_SHORT",
  "ARRAY_STORE_INT",
  "ARRAY_STORE_LONG",
  "ARRAY_STORE_FLOAT",
  "ARRAY_STORE_DOUBLE",
  "ARRAY_STORE_OBJECT",
  "ARRAY_STORE_UNDEF",
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
  "SET_FIELD_UNDEF",
  "IF_EQ_ZERO",
  "IF_NE_ZERO",
  "LOOKUP_SWITCH",
  "GOTO",
  "CALL_SUB",
  "CALL_INTERFACE_METHOD",
  "RETURN_VOID",
  "RETURN_BYTE",
  "RETURN_SHORT",
  "RETURN_INT",
  "RETURN_LONG",
  "RETURN_FLOAT",
  "RETURN_DOUBLE",
  "RETURN_OBJECT",
  "RETURN_UNDEF",
  "CROAK",
  "GET_EXCEPTION_VAR",
  "SET_EXCEPTION_VAR",
  "SET_EXCEPTION_UNDEF",
  "WEAKEN_FIELD",
  "NEW_BYTE_ARRAY",
  "NEW_SHORT_ARRAY",
  "NEW_INT_ARRAY",
  "NEW_LONG_ARRAY",
  "NEW_FLOAT_ARRAY",
  "NEW_DOUBLE_ARRAY",
  "CONCAT",
  "PUSH_EVAL",
  "POP_EVAL",
  "GET_PACKAGE_VAR_BYTE",
  "GET_PACKAGE_VAR_SHORT",
  "GET_PACKAGE_VAR_INT",
  "GET_PACKAGE_VAR_LONG",
  "GET_PACKAGE_VAR_FLOAT",
  "GET_PACKAGE_VAR_DOUBLE",
  "GET_PACKAGE_VAR_OBJECT",
  "SET_PACKAGE_VAR_BYTE",
  "SET_PACKAGE_VAR_SHORT",
  "SET_PACKAGE_VAR_INT",
  "SET_PACKAGE_VAR_LONG",
  "SET_PACKAGE_VAR_FLOAT",
  "SET_PACKAGE_VAR_DOUBLE",
  "SET_PACKAGE_VAR_OBJECT",
  "SET_PACKAGE_VAR_UNDEF",
  "GET_CONSTANT_BYTE",
  "GET_CONSTANT_SHORT",
  "GET_CONSTANT_INT",
  "GET_CONSTANT_LONG",
  "GET_CONSTANT_FLOAT",
  "GET_CONSTANT_DOUBLE",
  "CASE",
  "IF_CROAK_CATCH",
  "IF_CROAK_RETURN",
  "SET_CROAK_FLAG_TRUE",
  "MOVE_BYTE",
  "MOVE_SHORT",
  "MOVE_INT",
  "MOVE_LONG",
  "MOVE_FLOAT",
  "MOVE_DOUBLE",
  "MOVE_OBJECT",
  "MOVE_UNDEF",
  "PUSH_MORTAL",
  "LEAVE_SCOPE",
  "PUSH_ARG_BYTE",
  "PUSH_ARG_SHORT",
  "PUSH_ARG_INT",
  "PUSH_ARG_LONG",
  "PUSH_ARG_FLOAT",
  "PUSH_ARG_DOUBLE",
  "PUSH_ARG_OBJECT",
  "PUSH_ARG_UNDEF",
  "CHECK_CAST",
  "STRING_EQ",
  "STRING_NE",
  "STRING_GT",
  "STRING_GE",
  "STRING_LT",
  "STRING_LE",
  "ISA",
  "END_SUB",
};

SPVM_OPCODE* SPVM_OPCODE_new(SPVM_COMPILER* compiler) {
  SPVM_OPCODE* opcode = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_OPCODE));
  
  return opcode;
}

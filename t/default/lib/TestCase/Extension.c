#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>

#include <spvm_native.h>

static const char* MFILE = "TestCase/Extension.c";

int32_t SPNATIVE__TestCase__Extension__bpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int8_t value;
  SPVM_BPKGVAR(env, value, "TestCase::Extension", "$BYTE_VALUE", MFILE, __LINE__);
  
  stack[0].bval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__spkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int16_t value;
  SPVM_SPKGVAR(env, value,  "TestCase::Extension", "$SHORT_VALUE", MFILE, __LINE__);
  
  stack[0].sval = value;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ipkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t value;
  SPVM_IPKGVAR(env, value, "TestCase::Extension", "$INT_VALUE", MFILE, __LINE__);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__lpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int64_t value;
  SPVM_LPKGVAR(env, value, "TestCase::Extension", "$LONG_VALUE", MFILE, __LINE__);
  
  stack[0].lval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__fpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  float value;
  SPVM_FPKGVAR(env, value, "TestCase::Extension", "$FLOAT_VALUE", MFILE, __LINE__);
  
  stack[0].fval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__dpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  double value;
  SPVM_DPKGVAR(env, value, "TestCase::Extension", "$DOUBLE_VALUE", MFILE, __LINE__);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__opkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* value;
  SPVM_OPKGVAR(env, value, "TestCase::Extension", "$MINIMAL_VALUE", "TestCase::Minimal", MFILE, __LINE__);
  
  stack[0].oval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_bpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_SET_BPKGVAR(env, "TestCase::Extension", "$BYTE_VALUE", INT8_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_spkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_SET_SPKGVAR(env, "TestCase::Extension", "$SHORT_VALUE", INT16_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_ipkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_SET_IPKGVAR(env, "TestCase::Extension", "$INT_VALUE", INT32_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_lpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_SET_LPKGVAR(env, "TestCase::Extension", "$LONG_VALUE", INT64_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_fpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_SET_FPKGVAR(env, "TestCase::Extension", "$FLOAT_VALUE", FLT_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_dpkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_SET_DPKGVAR(env, "TestCase::Extension", "$DOUBLE_VALUE", DBL_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__set_opkgvar_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* minimal;
  SPVM_NEW(env, minimal, "TestCase::Minimal", MFILE, __LINE__);
  SPVM_SET_OPKGVAR(env, "TestCase::Extension", "$MINIMAL_VALUE", "TestCase::Minimal", minimal, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}


int32_t SPNATIVE__TestCase__Extension__has_callback_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->basic_type_id(env, "TestCase::Callback::Callback");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->has_callback(env, object, basic_type_id);
  
  stack[0].ival = match;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__is_type_test_minimals(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->basic_type_id(env, "TestCase::Minimal");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->is_type(env, object, basic_type_id, 1);
  
  stack[0].ival = match;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_byte_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_VALUE_byte x_in1 = stack[0].bval;
  SPVM_VALUE_byte x_in2 = stack[1].bval;
  
  *(stack[2].bref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_short_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_VALUE_short x_in1 = stack[0].sval;
  SPVM_VALUE_short x_in2 = stack[1].sval;
  
  *(stack[2].sref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_int_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_VALUE_int x_in1 = stack[0].ival;
  SPVM_VALUE_int x_in2 = stack[1].ival;
  
  *(stack[2].iref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_long_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_VALUE_long x_in1 = stack[0].lval;
  SPVM_VALUE_long x_in2 = stack[1].lval;
  
  *(stack[2].lref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_float_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_VALUE_float x_in1 = stack[0].fval;
  SPVM_VALUE_float x_in2 = stack[1].fval;
  
  *(stack[2].fref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__ref_double_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double x_in1 = stack[0].dval;
  double x_in2 = stack[1].dval;
  
  *(stack[2].dref) = x_in1 + x_in2;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_bfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_BFIELD(env, object, "TestCase::Simple", "byte_value", INT8_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_sfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_SFIELD(env, object, "TestCase::Simple", "short_value", INT16_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_ifield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_IFIELD(env, object, "TestCase::Simple", "int_value", INT32_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_lfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_LFIELD(env, object, "TestCase::Simple", "long_value", INT64_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_ffield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_FFIELD(env, object, "TestCase::Simple", "float_value", FLT_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_dfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_SET_DFIELD(env, object, "TestCase::Simple", "double_value", DBL_MIN, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_set_ofield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object_simple = stack[0].oval;
  
  int32_t field_id_object_simple_object_value = env->field_id(env, "TestCase::Simple", "object_value", "TestCase::Minimal");
  if (field_id_object_simple_object_value < 0) {
    return SPVM_EXCEPTION;
  }
  
  int32_t basic_type_id = env->basic_type_id(env, "TestCase::Minimal");
  if (basic_type_id < 0) {
    return SPVM_EXCEPTION;
  }
  void* object_minimal = env->new_obj(env, basic_type_id);
  
  int32_t field_id_minimal_x = env->field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return SPVM_EXCEPTION;
  }
  env->set_ifield(env, object_minimal, field_id_minimal_x, 3);
  
  env->set_ofield(env, object_simple, field_id_object_simple_object_value, object_minimal);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_bfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_byte byte_value;
  SPVM_BFIELD(env, byte_value, object, "TestCase::Simple", "byte_value", MFILE, __LINE__);
  
  if (byte_value == INT8_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_sfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_short short_value;
  SPVM_SFIELD(env, short_value, object, "TestCase::Simple", "short_value", MFILE, __LINE__);
  
  if (short_value == INT16_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_ifield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_int int_value;
  SPVM_IFIELD(env, int_value, object, "TestCase::Simple", "int_value", MFILE, __LINE__);
  
  if (int_value == INT32_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_lfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_long long_value;
  SPVM_LFIELD(env, long_value, object, "TestCase::Simple", "long_value", MFILE, __LINE__);
  
  if (long_value == INT64_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_ffield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_float float_value;
  SPVM_FFIELD(env, float_value, object, "TestCase::Simple", "float_value", MFILE, __LINE__);
  
  if (float_value == FLT_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_dfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  void* object = stack[0].oval;
  
  SPVM_VALUE_double double_value;
  SPVM_DFIELD(env, double_value, object, "TestCase::Simple", "double_value", MFILE, __LINE__);
  
  if (double_value == DBL_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_get_ofield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object_simple = stack[0].oval;
  
  int32_t field_id_object_simple_object_value = env->field_id(env, "TestCase::Simple", "object_value", "TestCase::Minimal");
  if (field_id_object_simple_object_value < 0) {
    return SPVM_EXCEPTION;
  }
  
  void* object_minimal = env->ofield(env, object_simple, field_id_object_simple_object_value);
  
  int32_t field_id_minimal_x = env->field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return SPVM_EXCEPTION;
  }
  
  int32_t x = env->ifield(env, object_minimal, field_id_minimal_x);
  
  if (x == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_use_strlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* string = stack[0].oval;
  
  int8_t* bytes = env->belems(env, string);
  
  int32_t length = (int32_t)strlen((char*)bytes);
  
  stack[0].ival = length;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_bfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_byte", "byte");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  int8_t value = env->bfield(env, test_case, field_id);
  
  stack[0].bval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_sfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_short", "short");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  int16_t value = env->sfield(env, test_case, field_id);
  
  stack[0].sval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_ifield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_int", "int");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  int32_t value = env->ifield(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_lfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_long", "long");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  int64_t value = env->lfield(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_ffield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_float", "float");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  float value = env->ffield(env, test_case, field_id);
  
  stack[0].fval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_dfield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "x_double", "double");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  double value = env->dfield(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_env_ofield(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->field_id(env, test_case, "minimal", "TestCase::Minimal");
  if (field_id < 0) {
    return SPVM_EXCEPTION;
  }
  
  void* value = env->ofield(env, test_case, field_id);
  
  stack[0].oval = value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t total = stack[0].ival + stack[1].ival;
  
  stack[0].ival = total;
  
  return SPVM_SUCCESS;
}


int32_t SPNATIVE__TestCase__Extension__add_iarray(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_nums1 = stack[0].oval;
  void* obj_nums2 = stack[1].oval;
  
  int32_t length = env->len(env, obj_nums1);
  
  int32_t* nums1 = env->ielems(env, obj_nums1);
  int32_t* nums2 = env->ielems(env, obj_nums2);
  
  void* onums3 = env->new_iarray(env, length);
  int32_t* nums3 = env->ielems(env, onums3);
  
  for (int32_t i = 0; i < length; i++) {
    nums3[i] = nums1[i] + nums2[i];
  }
  
  stack[0].oval = onums3;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__call_void_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception %s", "ppp", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_byte_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_short_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_int_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_long_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

float SPNATIVE__TestCase__Extension__call_float_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_double_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__call_object_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  SPVM_DIE("Exception", "TestCase/Extension.native/Extension.c", __LINE__);
}

int32_t SPNATIVE__TestCase__Extension__mortal_api(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  // Check if object count is zero in extension.t
  int32_t ref_count = 0;
  
  int32_t length = 10;
  // 1
  {
    void* sp_values = env->new_barray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 2
  {
    void* sp_values = env->new_sarray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 3
  {
    void* sp_values = env->new_iarray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 4
  {
    void* sp_values = env->new_larray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 5
  {
    void* sp_values = env->new_farray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 6
  {
    void* sp_values = env->new_larray(env, length);
    ref_count += env->ref_count(env, sp_values);
  }
  // 7
  {
    void* sp_values = env->new_str(env, "foo");
    ref_count += env->ref_count(env, sp_values);
  }
  // 8
  {
    int32_t basic_type_id = env->basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return SPVM_EXCEPTION;
    }
    void* sp_object = env->new_obj(env, basic_type_id);
    ref_count += env->ref_count(env, sp_object);
  }
  // 9
  {
    int32_t basic_type_id = env->basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return SPVM_EXCEPTION;
    }
    void* sp_objects = env->new_oarray(env, basic_type_id, 3);
    ref_count += env->ref_count(env, sp_objects);
  }
  // 10
  {
    int32_t basic_type_id = env->basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return SPVM_EXCEPTION;
    }
    void* sp_objects = env->new_oarray(env, basic_type_id, 3);
    ref_count += env->ref_count(env, sp_objects);
  }
  // 11
  {
    int32_t basic_type_id = env->basic_type_id(env, "TestCase::Pointer");
    if (basic_type_id < 0) {
      return SPVM_EXCEPTION;
    }
    void* sp_objects = env->new_pointer(env, basic_type_id, NULL);
    ref_count += env->ref_count(env, sp_objects);
  }
  
  if (ref_count == 11) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__enter_scope_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t length = 10;
  int32_t start_memory_blocks_count = env->memory_blocks_count(env);
  env->new_iarray(env, length);
  env->new_iarray(env, length);
  int32_t before_enter_memory_blocks_count = env->memory_blocks_count(env);
  int32_t before_leave_memory_blocks_count;
  {
    int32_t scope_id = env->enter_scope(env);

    env->new_iarray(env, length);
    env->new_iarray(env, length);
    env->new_iarray(env, length);
    
    before_leave_memory_blocks_count = env->memory_blocks_count(env);
    env->leave_scope(env, scope_id);
  }
  
  int32_t after_leave_memory_blocks_counts = env->memory_blocks_count(env);
  
  stack[0].ival = 0;
  if ((before_enter_memory_blocks_count - start_memory_blocks_count) == 2) {
    if (before_enter_memory_blocks_count == after_leave_memory_blocks_counts) {
      if ((before_leave_memory_blocks_count - before_enter_memory_blocks_count) == 3) {
        stack[0].ival = 1;
      }
    }
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__Extension__native_call_sub(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t sub_id = env->sub_id(env, "TestCase::Extension", "my_value", "int(int)");
  if (sub_id < 0) {
    return SPVM_EXCEPTION;
  }
  int32_t output;
  {
    stack[0].ival = 5;
    int32_t exception_flag = env->call_sub(env, sub_id, stack);
    if (exception_flag) {
      return SPVM_EXCEPTION;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return SPVM_SUCCESS;
}

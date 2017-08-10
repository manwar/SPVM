#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_api.h"

int32_t SPVM_EXTENTION_stdout__sum_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_BASE_OBJECT* array = args[0].object_value;
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* values = api->get_int_array_elements(api, array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  return total;
}

int32_t SPVM_EXTENTION_stdout__test1(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t sub_id = api->get_sub_id(api, "stdout::test2");
  
  SPVM_API_VALUE new_args[2];
  new_args[0].int_value = 5;
  new_args[1].int_value = 3;
  
  int32_t ret = api->call_int_sub(api, sub_id, new_args);
  
  int32_t num3 = num1 + num2 + ret;
  
  return num3;
}

int32_t SPVM_EXTENTION_stdout__test2(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t num3 = num1 * num2;
  
  return num3;
}

void SPVM_EXTENTION_stdout__print(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_BASE_OBJECT* array = args[0].object_value;

  int32_t length = api->get_array_length(api, array);
  int8_t* string = api->get_byte_array_elements(api, array);
  
  printf("%s\n", (char*)string);
}

void SPVM_EXTENTION_stdout__println(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_BASE_OBJECT* array = args[0].object_value;

  int32_t length = api->get_array_length(api, array);
  
  int8_t* string = api->get_byte_array_elements(api, array);

  printf("%s\n", (char*)string);
}

void SPVM_EXTENTION_stdout__println_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8 "\n", value);
}

void SPVM_EXTENTION_stdout__println_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16 "\n", value);
}

void SPVM_EXTENTION_stdout__println_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32 "\n", value);
}

void SPVM_EXTENTION_stdout__println_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64 "\n", value);
}

void SPVM_EXTENTION_stdout__println_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;

  printf("%f\n", value);
}

void SPVM_EXTENTION_stdout__println_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f\n", value);
}

void SPVM_EXTENTION_stdout__print_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8, value);
}

void SPVM_EXTENTION_stdout__print_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16, value);
}

void SPVM_EXTENTION_stdout__print_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32, value);
}

void SPVM_EXTENTION_stdout__print_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64, value);
}

void SPVM_EXTENTION_stdout__print_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;
  
  printf("%f", value);
}

void SPVM_EXTENTION_stdout__print_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f", value);
}

#ifndef SPVM_XS_UTIL_H
#define SPVM_XS_UTIL_H

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "spvm_api.h"
#include "spvm_type.h"
#include "spvm_object.h"

#include <stdint.h>

SPVM_API* SPVM_XS_UTIL_get_api() {
  SV* sv_api = get_sv("SPVM::API", 0);
  
  SPVM_API* api = (SPVM_API*)SvIV(SvRV(sv_api));
  
  return api;
}

int32_t SPVM_XS_UTIL_get_field_type_id(const char* package_name, const char* field_name) {
  // Field symbol table
  HV* hv_field_symtable = get_hv("SPVM::FIELD_SYMTABLE", 0);
  
  SV** sv_package_info_ptr = hv_fetch(hv_field_symtable, package_name, strlen(package_name), 0);
  if (sv_package_info_ptr) {
    SV* sv_package_info = *sv_package_info_ptr;
    HV* hv_package_info = (HV*)SvRV(sv_package_info);
    
    SV** sv_field_info_ptr = hv_fetch(hv_package_info, field_name, strlen(field_name), 0);
    if (sv_field_info_ptr) {
      SV* sv_field_info = *sv_field_info_ptr;
      HV* hv_field_info = (HV*)SvRV(sv_field_info);
      
      SV** sv_field_type_id_ptr = hv_fetch(hv_field_info, "type_id", strlen("type_id"), 0);
      if (sv_field_type_id_ptr) {
        SV* sv_field_type_id = *sv_field_type_id_ptr;
        int32_t field_type_id = SvIV(sv_field_type_id);
        
        return field_type_id;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

SV* SPVM_XS_UTIL_new_sv_byte_array(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Byte", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_string(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::String", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_short_array(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Short", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_int_array(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Int", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_long_array(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Long", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_float_array(SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Float", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_double_array(SPVM_OBJECT* object) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Double", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(object);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}

SV* SPVM_XS_UTIL_new_sv_object_array(int32_t type_code, int32_t type_id, SPVM_OBJECT* array) {
  
  // Create array
  HV* hv_array = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_array = sv_2mortal(newRV_inc((SV*)hv_array));
  HV* hv_class = gv_stashpv("SPVM::Array::Object", 0);
  sv_bless(sv_array, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(array);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_array, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_array;
}


SV* SPVM_XS_UTIL_new_sv_object(int32_t type_code, int32_t type_id, SPVM_OBJECT* object) {
  // Create object
  HV* hv_object = (HV*)sv_2mortal((SV*)newHV());
  SV* sv_object = sv_2mortal(newRV_inc((SV*)hv_object));
  HV* hv_class = gv_stashpv("SPVM::Object", 0);
  sv_bless(sv_object, hv_class);
  
  // Create content
  size_t iv_content = PTR2IV(object);
  SV* sviv_content = sv_2mortal(newSViv(iv_content));
  SV* sv_content = sv_2mortal(newRV_inc(sviv_content));
  
  // Set content
  hv_store(hv_object, "content", strlen("content"), SvREFCNT_inc(sv_content), 0);
  
  return sv_object;
}

SPVM_API_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_object) {
  
  if (SvOK(sv_object)) {
    HV* hv_object = (HV*)SvRV(sv_object);
    SV** sv_content_ptr = hv_fetch(hv_object, "content", strlen("content"), 0);
    
    assert(sv_content_ptr);
    
    SV* sv_content = *sv_content_ptr;
    SV* sviv_content = SvRV(sv_content);
    size_t iv_content = SvIV(sviv_content);
    SPVM_API_OBJECT* object = INT2PTR(SPVM_API_OBJECT*, iv_content);
    
    return object;
  }
  else {
    return NULL;
  }
}

#endif

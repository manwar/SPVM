use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_MAX = POSIX::FLT_MAX();
my $FLOAT_MIN = POSIX::FLT_MIN();
my $DOUBLE_MAX = POSIX::DBL_MAX();
my $DOUBLE_MIN = POSIX::DBL_MIN();
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# call_sub array
{
  # call_sub byte_array
  {
    my $sp_values = SPVM::new_byte_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_byte_array($sp_values), 6);
  }

  # call_sub short_array
  {
    my $sp_values = SPVM::new_short_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_short_array($sp_values), 6);
  }

  # call_sub int_array
  {
    my $sp_values = SPVM::new_int_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_int_array($sp_values), 6);
  }

  # call_sub long_array
  {
    my $sp_values = SPVM::new_long_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_long_array($sp_values), 6);
  }

  # call_sub float_array
  {
    my $sp_values = SPVM::new_float_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_float_array($sp_values), 2.0);
  }

  # call_sub double_array
  {
    my $sp_values = SPVM::new_double_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_double_array($sp_values), 2.0);
  }

  # call_sub
  {
    ok(SPVM::TestCase::call_sub_args_byte(0, $BYTE_MAX, $BYTE_MIN));
    ok(SPVM::TestCase::call_sub_args_short(0, $SHORT_MAX, $SHORT_MIN));
    ok(SPVM::TestCase::call_sub_args_int(0, $INT_MAX, $INT_MIN));
    ok(SPVM::TestCase::call_sub_args_long(0, $LONG_MAX, $LONG_MIN));
  }
}

# Call subroutine
{
  ok(SPVM::TestCase::call_sub_last_camma());
  ok(SPVM::TestCase::call_sub_undef(undef));
  
  {
    my $start_objects_count = SPVM::get_objects_count();
    SPVM::TestCase::call_sub_assign();
    my $end_objects_count = SPVM::get_objects_count();
    is($start_objects_count, $end_objects_count);
  }
}

# Call void subroutine
{
  ok(SPVM::TestCase::call_void());
}

# call_sub return array
{
  {
    my $sp_values = SPVM::TestCase::call_sub_return_byte_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Byte');
    SPVM::TestCase::call_sub_return_byte_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_short_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Short');
    SPVM::TestCase::call_sub_return_short_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_int_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Int');
    SPVM::TestCase::call_sub_return_int_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_long_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Long');
    SPVM::TestCase::call_sub_return_long_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_float_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Float');
    SPVM::TestCase::call_sub_return_float_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_double_array();
    is(ref $sp_values, 'SPVM::Core::Object::Array::Double');
    SPVM::TestCase::call_sub_return_double_array_check($sp_values);
  }
}

# Native subroutine
{
  my $sp_values = SPVM::new_int_array([1, 2, 3]);
  my $total = SPVM::CORE::sum_int($sp_values);
  is($total, 6);
}

# Call subroutine
{
  ok(SPVM::TestCase::sin());
  ok(SPVM::TestCase::cos());
  ok(SPVM::TestCase::tan());
}

# Default return value
{
  ok(SPVM::TestCase::default_return_value_byte());
  ok(SPVM::TestCase::default_return_value_short());
  ok(SPVM::TestCase::default_return_value_int());
  ok(SPVM::TestCase::default_return_value_long());
  ok(SPVM::TestCase::default_return_value_float());
  ok(SPVM::TestCase::default_return_value_double());
  ok(SPVM::TestCase::default_return_value_object());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);


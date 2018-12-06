use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Sub';

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Import sub
{
  ok(TestCase::Sub->test_import_sub);
}

# Retrun value automatical numeric convertion
{
  ok(TestCase::Sub->return_value_automatical_numeric_convertion);
}
# variable length arguments
{
  ok(TestCase::Sub->vaarg_objects_pass_each_values);
  ok(TestCase::Sub->vaarg_objects_pass_array);
  ok(TestCase::Sub->vaarg_pass_each_values);
  ok(TestCase::Sub->vaarg_pass_array);
}

# Anon sub
{
  ok(TestCase::Sub->anon_sub_capture);
  ok(TestCase::Sub->anon_sub_call_anon_sub);
  ok(TestCase::Sub->anon_sub_call_anon_sub_from_interface);
}

# Return value
{
  ok(TestCase::Sub->return_value_byte);
  ok(TestCase::Sub->return_value_short);
  ok(TestCase::Sub->return_value_int);
  ok(TestCase::Sub->return_value_long);
  ok(TestCase::Sub->return_value_float);
  ok(TestCase::Sub->return_value_double);
}

{
  ok(TestCase::Sub->push_arg_undef());
}

# call_sub array
{
  # call_sub barray
  {
    my $sp_values = SPVM::new_barray([1, 2, 3]);
    is(TestCase::Sub->call_sub_barray($sp_values), 6);
  }

  # call_sub sarray
  {
    my $sp_values = SPVM::new_sarray([1, 2, 3]);
    is(TestCase::Sub->call_sub_sarray($sp_values), 6);
  }

  # call_sub iarray
  {
    my $sp_values = SPVM::new_iarray([1, 2, 3]);
    is(TestCase::Sub->call_sub_iarray($sp_values), 6);
  }

  # call_sub larray
  {
    my $sp_values = SPVM::new_larray([1, 2, 3]);
    is(TestCase::Sub->call_sub_larray($sp_values), 6);
  }

  # call_sub farray
  {
    my $sp_values = SPVM::new_farray([0.5, 0.5, 1.0]);
    is(TestCase::Sub->call_sub_farray($sp_values), 2.0);
  }

  # call_sub darray
  {
    my $sp_values = SPVM::new_darray([0.5, 0.5, 1.0]);
    is(TestCase::Sub->call_sub_darray($sp_values), 2.0);
  }

  # call_sub
  {
    ok(TestCase::Sub->call_sub_args_byte(0, $BYTE_MAX, $BYTE_MIN));
    ok(TestCase::Sub->call_sub_args_short(0, $SHORT_MAX, $SHORT_MIN));
    ok(TestCase::Sub->call_sub_args_int(0, $INT_MAX, $INT_MIN));
    ok(TestCase::Sub->call_sub_args_long(0, $LONG_MAX, $LONG_MIN));
  }
}

# Call subroutine
{
  ok(TestCase::Sub->call_sub_last_camma());
  ok(TestCase::Sub->call_sub_undef(undef));
  
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    TestCase::Sub->call_sub_assign();
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($start_memory_blocks_count, $end_memory_blocks_count);
  }
}

# Call void subroutine
{
  ok(TestCase::Sub->call_void());
}



# call_sub return array
{
  {
    my $sp_values = TestCase::Sub->call_sub_return_barray();
    TestCase::Sub->call_sub_return_barray_check($sp_values);
  }
  {
    my $sp_values = TestCase::Sub->call_sub_return_sarray();
    TestCase::Sub->call_sub_return_sarray_check($sp_values);
  }
  {
    my $sp_values = TestCase::Sub->call_sub_return_iarray();
    TestCase::Sub->call_sub_return_iarray_check($sp_values);
  }
  {
    my $sp_values = TestCase::Sub->call_sub_return_larray();
    TestCase::Sub->call_sub_return_larray_check($sp_values);
  }
  {
    my $sp_values = TestCase::Sub->call_sub_return_farray();
    TestCase::Sub->call_sub_return_farray_check($sp_values);
  }
  {
    my $sp_values = TestCase::Sub->call_sub_return_darray();
    TestCase::Sub->call_sub_return_darray_check($sp_values);
  }
}

# Default return value
{
  ok(TestCase::Sub->default_return_value_byte());
  ok(TestCase::Sub->default_return_value_short());
  ok(TestCase::Sub->default_return_value_int());
  ok(TestCase::Sub->default_return_value_long());
  ok(TestCase::Sub->default_return_value_float());
  ok(TestCase::Sub->default_return_value_double());
  ok(TestCase::Sub->default_return_value_object());
}

{
  ok(TestCase::Sub->call_sub_nest());
}

# Argument convetion
{
  ok(TestCase::Sub->call_sub_args_convertion());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

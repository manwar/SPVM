use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Enum';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Enumeration
{
  ok(TestCase::Enum->enum_int());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

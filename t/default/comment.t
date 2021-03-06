use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Comment::LF';
use SPVM 'TestCase::Comment::CR';
use SPVM 'TestCase::Comment::CRLF';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

{
  ok(TestCase::Comment::LF->comment);
  ok(TestCase::Comment::CR->comment);
  ok(TestCase::Comment::CRLF->comment);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

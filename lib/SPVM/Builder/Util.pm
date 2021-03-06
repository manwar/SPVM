package SPVM::Builder::Util;

use strict;
use warnings;
use Carp 'confess';
use Config;
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';
use File::Basename 'dirname';

use SPVM::Builder::Config;

# SPVM::Builder::Util is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules except for SPVM::Builder::Config.

sub unindent {
  my $str = shift;
  my $min = min map { m/^([ \t]*)/; length $1 || () } split "\n", $str;
  $str =~ s/^[ \t]{0,$min}//gm if $min;
  return $str;
}

sub extract_usage {
  my $file = @_ ? "$_[0]" : (caller)[1];

  open my $handle, '>', \my $output;
  pod2usage -exitval => 'noexit', -input => $file, -output => $handle;
  $output =~ s/^.*\n|\n$//;
  $output =~ s/\n$//;

  return SPVM::Builder::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
}

sub get_dll_func_address {
  my ($dll_file, $dll_func_name) = @_;
  
  my $native_address;
  
  if ($dll_file) {
    my $dll_libref = DynaLoader::dl_load_file($dll_file);
    if ($dll_libref) {
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $dll_func_name);
      unless ($native_address) {
        my $dl_error = DynaLoader::dl_error();
        confess "Can't find function \"$dll_func_name\" in \"$dll_file\": $dl_error";
      }
    }
    else {
      my $dl_error = DynaLoader::dl_error();
      confess "Can't load dll file \"$dll_file\": $dl_error";
    }
  }
  else {
    confess "DLL file is not specified";
  }
  
  return $native_address;
}

sub convert_module_file_to_dll_category_file {
  my ($module_file, $category) = @_;
  
  my $dlext = $Config{dlext};
  $module_file =~ s/\.[^.]+$//;
  my $dll_category_file = $module_file;
  $dll_category_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dll_category_file;
}

sub convert_package_name_to_dll_category_rel_file {
  my ($package_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $dll_category_rel_file = convert_package_name_to_rel_file_without_ext($package_name);
  $dll_category_rel_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dll_category_rel_file;
}

sub convert_package_name_to_category_rel_file_with_ext {
  my ($package_name, $category, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= $category eq 'native' ? ".$ext" : ".$category.$ext";
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_category_rel_file_without_ext {
  my ($package_name, $category, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= $category eq 'native' ? "" : ".$category";
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_rel_file {
  my ($package_name) = @_;
  
  my $rel_file = $package_name;
  $rel_file =~ s/::/\//g;
  $rel_file .= '.spvm';
  
  return $rel_file;
}

sub convert_package_name_to_rel_dir {
  my ($package_name) = @_;
  
  my $rel_dir;
  if ($package_name =~ /::/) {
    my $rel_file = $package_name;
    $rel_file =~ s/::/\//g;
    $rel_dir = dirname $rel_file;
  }
  else {
    $rel_dir = '';
  }
  
  return $rel_dir;
}

sub convert_package_name_to_rel_file_with_ext {
  my ($package_name, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= ".$ext";
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_rel_file_without_ext {
  my ($package_name) = @_;
  
  my $rel_file_without_ext = $package_name;
  $rel_file_without_ext =~ s/::/\//g;
  
  return $rel_file_without_ext;
}

sub remove_package_part_from_file {
  my ($file, $package_name) = @_;
  
  $file =~ s/\.spvm$//;
  my $package_file = $package_name;
  $package_file =~ s/::/\//g;
  $file =~ s/$package_file$//;
  $file =~ s/[\\\/]$//;
  
  return $file;
}

sub create_make_rule_native {
  my $package_name = shift;
  
  create_package_make_rule($package_name, 'native');
}

sub create_make_rule_precompile {
  my $package_name = shift;
  
  create_package_make_rule($package_name, 'precompile');
}

sub create_package_make_rule {
  my ($package_name, $category) = @_;
  
  my $make_rule;
  
  # dynamic section
  $make_rule
  = "dynamic :: ";

  my $package_name_under_score = $package_name;
  $package_name_under_score =~ s/:/_/g;
  
  my $target_name = "spvm_${category}_$package_name_under_score ";
  $make_rule
    .= "$target_name ";
  $make_rule .= "\n\n";
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = 'lib';

  my $package_rel_file = convert_package_name_to_rel_file($package_name);
  
  my $noext_file = $package_rel_file;
  $noext_file =~ s/\.[^\.]+$//;
  
  my $spvm_file = $noext_file;
  $spvm_file .= '.spvm';
  $spvm_file = "$src_dir/$spvm_file";

  my $c_file = $noext_file;
  $c_file .= '.c';
  $c_file = "$src_dir/$c_file";

  my $config_file = $noext_file;
  $config_file .= '.config';
  $config_file = "$src_dir/$config_file";

  # Dependency files
  my @deps;
  
  # Dependency c source files
  push @deps, grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/$package_rel_file/*";
  
  # Dependency module file
  push @deps, $spvm_file, $c_file, $config_file;
  
  # Shared library file
  my $dll_rel_file = convert_package_name_to_dll_category_rel_file($package_name, $category);
  my $dll_file = "blib/lib/$dll_rel_file";
  
  # Get source files
  $make_rule
    .= "$target_name :: $dll_file\n\n";
  $make_rule
    .= "$dll_file :: @deps\n\n";
  $make_rule
    .= "\t$^X -Mblib -MSPVM::Builder -e \"SPVM::Builder->new(build_dir => 'spvm_build')->build_dll_${category}_dist('$package_name')\"\n\n";
  
  return $make_rule;
}

1;

=head1 NAME

SPVM::Builder::Util - Build Utilities

=head1 DESCRIPTION

SPVM::Builder::Util is building utilities.

=head1 FUNCTIONS

=head2 create_make_rule_native

Create native compile make rule.

This is used in Makefile.PL of your distributed module.
  
  # Makefile.PL
  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

Create precompile make rule.

This is used in Makefile.PL of your distributed module.

  sub MY::postamble {

    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }


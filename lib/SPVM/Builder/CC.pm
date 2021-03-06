package SPVM::Builder::CC;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Config;

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Config;

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub category { shift->{category} }

sub quiet { shift->{quiet} }

sub builder { shift->{builder} }

sub build {
  my ($self, $opt) = @_;
  
  my $package_names = $self->builder->get_package_names;
  for my $package_name (@$package_names) {
    
    my $category = $self->{category};
    my $sub_names;
    if ($category eq 'native') {
      $sub_names = $self->builder->get_native_sub_names($package_name)
    }
    elsif ($category eq 'precompile') {
      $sub_names = $self->builder->get_precompile_sub_names($package_name)
    }
    
    if (@$sub_names) {
      # Shared library is already installed in distribution directory
      my $dll_file = $self->get_dll_file_dist($package_name);
      
      # Try runtime compile if shared objectrary is not found
      unless (-f $dll_file) {
        if ($category eq 'native') {
          $self->build_dll_native_runtime($package_name, $sub_names);
        }
        elsif ($category eq 'precompile') {
          $self->build_dll_precompile_runtime($package_name, $sub_names);
        }
        $dll_file = $self->get_dll_file_runtime($package_name);
      }
      $self->bind_subs($dll_file, $package_name, $sub_names);
    }
  }
}

sub copy_dll_to_build_dir {
  my ($self, $package_name, $category) = @_;
  
  my $dll_file = $self->get_dll_file_dist($package_name);
  
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $category);
  
  my $build_dir = $self->builder->{build_dir};
  
  my $dll_build_dir = "$build_dir/work/lib/$dll_rel_file";
  
  my $dll_build_dir_dir = dirname $dll_build_dir;
  
  mkpath $dll_build_dir_dir;
  
  copy $dll_file, $dll_build_dir
    or confess "Can't copy $dll_file to $dll_build_dir";
}

sub get_dll_file_runtime {
  my ($self, $package_name) = @_;
  
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $build_dir = $self->{build_dir};
  my $lib_dir = "$build_dir/work/lib";
  my $dll_file = "$lib_dir/$dll_rel_file";
  
  return $dll_file;
}

sub create_cfunc_name {
  my ($self, $package_name, $sub_name) = @_;
  
  my $category = $self->category;
  my $prefix = 'SP' . uc($category) . '__';
  
  # Precompile Subroutine names
  my $sub_abs_name_under_score = "${package_name}::$sub_name";
  $sub_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$sub_abs_name_under_score";
  
  return $cfunc_name;
}

sub get_config_runtime {
  my ($self, $package_name, $category) = @_;
  
  my $module_file = $self->builder->get_module_file($package_name);
  my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    open my $config_fh, '<', $config_file
      or confess "Can't open $config_file: $!";
    my $config_content = do { local $/; <$config_fh> };
    $bconf = eval "$config_content";
    if (my $messge = $@) {
      confess "Can't parser $config_file: $@";
    }
  }
  else {
    if ($category eq 'native') {
      confess "Can't find $config_file: $@";
    }
    else {
      $bconf = SPVM::Builder::Config->new_default;
    }
  }
  
  return $bconf;
}

sub bind_subs {
  my ($self, $dll_file, $package_name, $sub_names) = @_;
  
  # Load pre-required dlls
  my $category = $self->category;
  my $bconf = $self->get_config_runtime($package_name, $category);
  my $dll_infos = $bconf->parse_dll_infos;
  
  my $libpth = $Config{libpth};
  my @dll_load_paths = split(/ +/, $libpth);
  my $build_lib_dir = $self->{build_dir} . '/lib';
  push @dll_load_paths, $build_lib_dir;
  
  for my $dll_info (@$dll_infos) {
    if ($dll_info->{type} eq 'L') {
      push @dll_load_paths, $dll_info->{name};
    }
    elsif ($dll_info->{type} eq 'l') {
      for my $dll_load_path (reverse @dll_load_paths) {
        my $name = $dll_info->{name};
        my $dlext = $Config{dlext};
        my $dll_file = "$dll_load_path/lib$name.$dlext";
        if (-f $dll_file) {
          my $dll_libref = DynaLoader::dl_load_file($dll_file);
          unless ($dll_libref) {
            my $dl_error = DynaLoader::dl_error();
            confess "Can't load pre required dll file \"$dll_file\": $dl_error";
          }
          last;
        }
      }
    }
  }
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($package_name, $sub_name);
    my $cfunc_address = SPVM::Builder::Util::get_dll_func_address($dll_file, $cfunc_name);
    
    if ($category eq 'native') {
      $self->bind_sub_native($package_name, $sub_name, $cfunc_address);
    }
    elsif ($category eq 'precompile') {
      $self->bind_sub_precompile($package_name, $sub_name, $cfunc_address);
    }
  }
}

sub build_dll {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Compile source file and create object files
  my $object_file = $self->compile($package_name, $opt);
  
  # Link object files and create shared objectrary
  $self->link(
    $package_name,
    $sub_names,
    $object_file,
    $opt
  );
}

sub compile {
  my ($self, $package_name, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  # Input directory
  my $src_dir = $opt->{src_dir};

  # Temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  my $category = $self->category;
 
  my $package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $work_object_dir = "$object_dir/$package_rel_dir";
  mkpath $work_object_dir;
  
  # Package base name
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    open my $config_fh, '<', $config_file
      or confess "Can't open $config_file: $!";
    my $config_content = do { local $/; <$config_fh> };
    $bconf = eval "$config_content";
    if (my $messge = $@) {
      confess "Can't parser $config_file: $@";
    }
  }
  else {
    $bconf = SPVM::Builder::Config->new_default;;
  }

  # Quiet output
  my $quiet = defined $bconf->get_quiet ? $bconf->get_quiet : $self->quiet;
  
  # Source file
  my $src_rel_file_no_ext = SPVM::Builder::Util::convert_package_name_to_category_rel_file_without_ext($package_name, $category);
  my $src_file_no_ext = "$src_dir/$src_rel_file_no_ext";
  my $src_ext = $bconf->get_ext;
  unless (defined $src_ext) {
    confess "Source extension is not specified";
  }
  my $src_file = "$src_file_no_ext.$src_ext";
  unless (-f $src_file) {
    confess "Can't find source file $src_file";
  }

  # CBuilder configs
  my $ccflags = $bconf->get_ccflags;
  
  # Default include path
  $bconf->add_ccflags("-I$build_dir/include");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;

  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  
  # Object file
  my $object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'o');
  my $object_file = "$object_dir/$object_rel_file";
  
  # Do compile. This is same as make command
  my $do_compile;
  if ($package_name =~ /^anon/) {
    $do_compile = 1;
  }
  else {
    if (!-f $object_file) {
      $do_compile = 1;
    }
    else {
      if (defined $bconf->get_cache && !$bconf->get_cache) {
        $do_compile = 1;
      }
      else {
        # Source file modified time is newer than object file
        my $mod_time_src = (stat($src_file))[9];
        my $mod_time_object = (stat($object_file))[9];
        if ($mod_time_src > $mod_time_object) {
          $do_compile = 1;
        }
        else {
          # Config file modified time is newer than object file
          if (-f $config_file) {
            my $mod_time_config = (stat($config_file))[9];
            my $mod_time_object = (stat($object_file))[9];
            if ($mod_time_config > $mod_time_object) {
              $do_compile = 1;
            }
          }
        }
      }
    }
  }
  
  if ($do_compile) {
    eval {
      # Compile source file
      $cbuilder->compile(
        source => $src_file,
        object_file => $object_file,
        extra_compiler_flags => $bconf->get_extra_compiler_flags,
      );
    };
    if (my $error = $@) {
      confess $error;
    }
  }
  
  return $object_file;
}

sub link {
  my ($self, $package_name, $sub_names, $object_file, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  # Input directory
  my $src_dir = $opt->{src_dir};

  # Work temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $lib_dir = $opt->{lib_dir};
  unless (defined $lib_dir && -d $lib_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared object file
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $dll_file = "$lib_dir/$dll_rel_file";

  # Create temporary package directory
  my $tmp_package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $tmp_package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $tmp_package_dir = "$object_dir/$tmp_package_rel_dir";
  mkpath $tmp_package_dir;
  
  # Category
  my $category = $self->category;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    open my $config_fh, '<', $config_file
      or confess "Can't open $config_file: $!";
    my $config_content = do { local $/; <$config_fh> };
    $bconf = eval "$config_content";
    if (my $messge = $@) {
      confess "Can't parser $config_file: $@";
    }
  }
  else {
    $bconf = SPVM::Builder::Config->new_default;;
  }

  # Quiet output
  my $quiet = defined $bconf->get_quiet ? $bconf->get_quiet : $self->quiet;
  
  # CBuilder configs
  my $lddlflags = $bconf->get_lddlflags;

  # Default library path
  $bconf->add_lddlflags("-L$build_dir/lib");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $category = $self->category;
    my $category_uc = uc $category;
    my $cfunc_name = "SPVM_${category_uc}_${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $tmp_dll_file;
  eval {
    $tmp_dll_file = $cbuilder->link(
      objects => [$object_file],
      module_name => $package_name,
      dl_func_list => $cfunc_names,
      extra_linker_flags => $bconf->get_extra_linker_flags,
    );
  };
  if (my $error = $@) {
    confess $error;
  }

  # Create shared object blib directory
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file_without_ext($package_name);
  my $dll_dir = dirname "$lib_dir/$package_rel_file_without_ext";
  mkpath $dll_dir;
  
  # Move shared objectrary file to blib directory
  move($tmp_dll_file, $dll_file)
    or die "Can't move $tmp_dll_file to $dll_file";
  
  return $dll_file;
}

sub get_dll_file_dist {
  my ($self, $package_name) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_module_file = $self->builder->get_module_file($package_name);
  
  my $dll_file = SPVM::Builder::Util::convert_module_file_to_dll_category_file($module_module_file, $self->category);
  
  return $dll_file;
}

sub build_dll_precompile_runtime {
  my ($self, $package_name, $sub_names) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  # Object directory
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  
  # Source directory
  my $src_dir = "$build_dir/work/src";
  mkpath $src_dir;
  
  # Lib directory
  my $lib_dir = "$build_dir/work/lib";
  mkpath $lib_dir;
  
  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_native_runtime {
  my ($self, $package_name, $sub_names) = @_;
  
  my $module_file = $self->builder->get_module_file($package_name);
  my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  
  my $lib_dir = "$build_dir/work/lib";
  mkpath $lib_dir;
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_precompile_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $object_dir = "spvm_build/work/object";
  mkpath $object_dir;
  
  my $src_dir = "spvm_build/work/src";
  mkpath $src_dir;

  my $lib_dir = 'blib/lib';
  
  my $category = $self->category;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  my $config_file = "$src_dir/$module_base_name.config";

  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_native_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $src_dir = 'lib';

  my $object_dir = "spvm_build/work/object";
  mkpath $object_dir;

  my $lib_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared object
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub create_source_precompile {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $src_dir = $opt->{src_dir};
  mkpath $src_dir;
  
  my $category = 'precompile';
  
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file_without_ext($package_name);
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $source_file = "$src_dir/$package_rel_file_without_ext.$category.c";
  
  my $source_dir = "$src_dir/$package_rel_dir";
  mkpath $source_dir;

  my $package_csource = $self->build_package_csource_precompile($package_name, $sub_names);
  
  my $is_create_source_file;
  # Anon sub
  if ($package_name =~ /^anon/) {
    $is_create_source_file = 1;
  }
  # Normal sub
  else {
    # Get old csource source
    my $old_package_csource;
    if (-f $source_file) {
      open my $fh, '<', $source_file
        or die "Can't open $source_file";
      $old_package_csource = do { local $/; <$fh> };
    }
    else {
      $old_package_csource = '';
    }
    
    if ($package_csource ne $old_package_csource) {
      $is_create_source_file = 1;
    }
    else {
      $is_create_source_file = 0;
    }
  }
  
  # Create source fil
  if ($is_create_source_file) {
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $package_csource;
    close $fh;
  }
}

1;

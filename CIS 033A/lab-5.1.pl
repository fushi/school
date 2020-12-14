#!/usr/bin/perl -w

#Lab 5, Part 1

use strict;
use File::Copy;

umask(0000);

die "Usage: $0 <directory> <directory> <number>\n" if @ARGV != 3;
die "$ARGV[2] is not a valid number\n" if $ARGV[2] !~ /^\d+(\.\d+)?$/;
opendir(OLD, $ARGV[1]) or die "$ARGV[1] could not be opened\n";
mkdir($ARGV[0]) or die "$ARGV[0] could not be created\n";
chmod 0700, $ARGV[0] or die "Cannot chmod $ARGV[0]\n";

my ($new_dir, $old_dir, $min_age) = @ARGV;
my ($old_path, $new_path, $file);

foreach $file (readdir(OLD)){
	$old_path = "$old_dir/$file";
	$new_path = "$new_dir/$file";

	next if (-d $old_path || -M $old_path < $min_age);

	if(!copy($old_path, $new_path)){
		print "Could not copy $old_path to $new_path\n";
		next;
	}

	print "Could not chmod $new_path\n" if !chmod 0700, $new_path;
}

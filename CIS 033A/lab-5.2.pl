#!/usr/bin/perl -w

#Lab 5, Part 2

use strict;

die "Usage: $0 <directory> <directory>\n" if @ARGV != 2;
opendir(D, $ARGV[0]) or die "$ARGV[0] could not be opened\n";

my($dir_1, $dir_2, $file) = @ARGV;
my($path_1, $path_2);

foreach $file (readdir(D)){

	$path_1 = "$dir_1/$file";
	$path_2 = "$dir_2/$file";

	next if(!-e $path_2 || !-T $path_2 || !-T $path_1);

	print "Cannot Delete $path_2\n" if(-s $path_1 == -s $path_2 && !unlink($path_2));
}


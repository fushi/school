#!/usr/bin/perl -w

#Lab 4, Part 1

use strict;

die "Usage: $0 <output file> <integer>\n" if @ARGV < 2;
open(FOUT, ">$ARGV[0]") or die "Could not open $ARGV[1] for writing\n";
die "$ARGV[1] is not a valid integer\n" if $ARGV[1] =~ /\D/;

my ($out_file, $min_size, @dirs) = @ARGV;

my($dir,$file, $path, $file_size);

foreach $dir (sort(@dirs)){
	
	my ($banner, %files) = "#" x 70;

	if(!opendir(D, $dir)){
		print "Cannot open $dir\n";
		next;
	}
	
	foreach $file (sort(readdir(D))){
		$path = "$dir/$file";
		$file_size = -s "$path";

		$files{$file} = $file_size if (-T $path && ($file_size  >= $min_size));
	}

	printf FOUT ("%s\n%s\n%-65s%s\n%s\n", $banner, "Directory: ".$dir, "File", "Size", $banner) if %files;

	printf FOUT ("%-65s%d\n", $_, $files{$_}) foreach (sort keys %files);
}


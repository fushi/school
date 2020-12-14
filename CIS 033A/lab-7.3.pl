#!/usr/bin/perl -w

#Lab 7, Part 3

use strict;
use Cwd 'abs_path';

my ($outfile, @dirs) = @ARGV;

die "Usage: $0 <outfile> <dir> (...<dir>)" if !@dirs;
open(FOUT, ">$outfile") or die "Cannot open $outfile for writing.\n";

my ($dir, %hash);
my ($first) = 1;

foreach $dir (@dirs){
	if (!opendir(D, $dir)){
		print "Could not open $dir\n";
		next;
	}	
	$hash{abs_path($dir)} = {map{$_ => (stat "$dir/$_")[2] & 0777} readdir(D)};
}

foreach $dir (sort keys %hash){
	$first ? $first = 0 : print FOUT "\n\n";
	print FOUT "$dir\n", "-" x length($dir);
	printf FOUT "\n%-40s%3o", $_, $hash{$dir}{$_} foreach (sort {$hash{$dir}{$b} <=> $hash{$dir}{$a}} keys %{$hash{$dir}});
}

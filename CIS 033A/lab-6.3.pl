#!/usr/bin/perl -w

#Lab 6, Part 3

use strict;

die "Usage: $0 <directory>\n" if @ARGV != 1;
opendir(D, "$ARGV[0]") or die "$ARGV[0] could not be opened.\n";

our ($dir) = $ARGV[0];

print map{my ($time) = scalar(localtime((stat "$dir/$_")[9])); sprintf("%-40s%-40s\n",$_, $time)} sort by_mod_date readdir(D);


sub by_mod_date{
	my ($dateA) = (stat "$dir/$a")[9];
	my ($dateB) = (stat "$dir/$b")[9];

	$dateB <=> $dateA;
}

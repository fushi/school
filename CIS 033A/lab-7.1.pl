#!/usr/bin/perl -w

#Lab 7, Part 1

use strict;

die "Usage: $0 <infile> <outfile>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "$ARGV[0] could not be read from.\n";
open(FOUT, ">$ARGV[1]") or die "$ARGV[0] could not be written to.\n";

my ($first, %states) = 1;

while(<FIN>){
	chomp;
	my ($name, $sob) = (split /:/)[0,3];

	push (@{$states{$sob}}, $name) if $name;
}

foreach(sort keys %states){
	
	$first ? $first = 0 : print FOUT "\n\n";
	
	print FOUT "$_\n", "-" x length($_), "\n";

	print FOUT join ("\n", sort @{$states{$_}});
}

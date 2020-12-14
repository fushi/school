#!/usr/bin/perl -w

#Lab 4, Part 2

use strict;

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

while(<FIN>){
	tr/a-zA-Z/d-zabcD-ZABC/;
	print FOUT;
}

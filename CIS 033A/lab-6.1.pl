#!/usr/bin/perl -w

#Lab 6, Part 1

use strict;

die "Usage: $0 <infile> <outfile>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "$ARGV[0] could not be read from.\n";
open(FOUT, ">$ARGV[1]") or die "$ARGV[1] could not be written to.\n";

while(<FIN>){
	print FOUT if /^(\d+)/.../$1/;
}

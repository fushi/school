#!/usr/bin/perl -w

#Lab 2, Part 2

use strict;

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

my @nums;

while (<FIN>){
     push (@nums, /^[-+]?[1-9]\d*$/g) foreach (split);
     print FOUT join(" ", @nums), "\n";
}

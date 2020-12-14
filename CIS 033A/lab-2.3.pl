#!/usr/bin/perl -w

#Lab 2, Part 3

use strict;

die "Usage: $0 <input file> <output file> <unsigned integer>\n" if @ARGV != 3;
die "Usage: $ARGV[2] is not an unsigned integer" if $ARGV[2] !~ /^\d+$/;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

my $index = $ARGV[2];
my ($name, @scores);

while(<FIN>){
     ($name, @scores) = split;
     if (@scores < $index){print FOUT "$name $scores[-1]\n";}
     else {print FOUT "$name $scores[$index - 1]\n";}
}

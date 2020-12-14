#!/usr/bin/perl -w

#Lab 6, Part 4

use strict;

our ($offset, $string) = @ARGV[2,3];


die "Usage: $0 <infile> <outfile> <unsigned int> <string>\n" if @ARGV != 4;
die "$offset is not an acceptable number.\n" if $offset !~ /^\d+$/ || $offset == 0;
open(FIN, "$ARGV[0]") or die "$ARGV[0] could not be read from.\n";
open(FOUT, ">$ARGV[1]") or die "$ARGV[1] could not be written to.\n";

$offset--;

print FOUT map{my ($index) = index($_, $string); $index > $offset || $index == -1 ? ():substr($_, $index);}<FIN>;

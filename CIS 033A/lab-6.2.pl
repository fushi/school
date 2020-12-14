#!/usr/bin/perl -w

#Lab 6, Part 2

use strict;

our ($int, $letter, $dna) = @ARGV[2,3];

die "Usage: $0 <infile> <outfile> <unsigned int> <[tcag]>\n" if @ARGV != 4;
die "$int is not an unsigned integer.\n" if $int !~ /^\d+$/;
die "$letter is not an t, c, a, or g.\n" if $letter !~ /^[tcag]$/;
open(FIN, "$ARGV[0]") or die "$ARGV[0] could not be read from.\n";
open(FOUT, ">$ARGV[1]") or die "$ARGV[1] could not be written to.\n";

print FOUT grep{$dna = (split(":"))[1]; $int <= $dna =~ s/(\Q$letter\E)/$1/g}<FIN>;

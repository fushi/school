#!/usr/bin/perl -w

#Lab 3, Part 2

use strict;

die "Usage: $0 <input file> <integer>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
die "$ARGV[1] is not a legal integer\n" if $ARGV[1] =~ /\D/ || $ARGV[1] == 0;

my (%people);
my ($times, $key) = $ARGV[1];

while(<FIN>){
     ($key) = /^(.+)\s+\d+$/;
     $people{$key}++;
}

foreach (sort keys %people){
     print "$_\n" if $people{$_} >= $times;
}

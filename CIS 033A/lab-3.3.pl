#!/usr/bin/perl -w

#Lab 3, Part 3

use strict;

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

my (%hash);
my (@hits);
my ($site);

while(<FIN>){
     ($site, @hits) = split;
     @hits = sort {$a <=> $b} @hits;
     $hash{$site} = $hits[-1];
}

print FOUT "$_ $hash{$_}\n" foreach (sort {$hash{$b} <=> $hash{$a} or $a cmp $b} keys %hash);

#!/usr/bin/perl -w

#Lab 3, Part 1

use strict;

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

my (%city_freq, %city_high, %city_low);
my ($cityname, $high, $low);

while(<FIN>){
     ($cityname, $high, $low) = /^(.+):(\d+) (\d+)$/;

     $city_freq{$cityname} ++;
     $city_high{$cityname} += $high;
     $city_low{$cityname} += $low;
}

print FOUT "$_:".$city_high{$_}/$city_freq{$_}. " " .$city_low{$_}/$city_freq{$_} . "\n" foreach (sort keys %city_freq);

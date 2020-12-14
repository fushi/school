#!/usr/bin/perl -w

#Lab 2, Part 1

use strict;

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

my ($strings, $lines) = (0,0);

while (<FIN>){
     foreach(/[a-zA-Z]+/g){
          print FOUT uc() . "\n";
          $strings++;
     }
     $lines++;
}
print FOUT "There were $strings letter strings, averaging " . $strings/$lines . " per line.\n";

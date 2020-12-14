#!/usr/bin/perl

use strict;

die "Usage: $0 <input file> <output file> <min hits> <freq>\n"
	unless @ARGV == 4;
die "Usage: $ARGV[2] is not an unsigned non-zero int"
	unless ($ARGV[2] =~ /^\d+$/ && $ARGV[2] != 0);
die "Usage: $ARGV[3] is not an int between 1 and 12"
	unless ($ARGV[3] =~ /^\d+$/ && $ARGV[3] != 0 && $ARGV[3] < 12 );
	
open(FIN, "$ARGV[0]")
	or die "Could not open $ARGV[0] for reading\n";
	
open(FOUT, ">$ARGV[1]")
	or die "Could not open $ARGV[1] for writing\n";

my($minHits, $freq) = @ARGV[2,3];

print FOUT grep{(grep{$_ >= $minHits} (split (/\s+/))[1 .. 12]) >= $freq} <FIN>;

#!/usr/bin/perl -w

#Lab 4, Part 3

use strict;

die "Usage: $0 <output file> <directory>\n" if @ARGV != 2;
open(FOUT, ">$ARGV[0]") or die "Could not open $ARGV[0] for writing\n";
opendir(D, $ARGV[1]) or die "$ARGV[1] could not be opened\n";

my(%fileage);

$fileage{$_} = -M "$ARGV[1]/$_" foreach (readdir(D));

printf FOUT ("%-50s%f\n", $_, $fileage{$_}) foreach (sort({$fileage{$a} <=> $fileage{$b} || $a cmp $b} keys %fileage));

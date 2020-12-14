#!/usr/bin/perl -w

#Lab 5, Part 3

use strict;
use File::Find;

die "Usage: $0 <directory> <outfile>\n" if @ARGV != 2;
die "$ARGV[0] is not a directory\n" if !-d $ARGV[0];
open(FOUT, ">$ARGV[1]") or die "$ARGV[1] could not be written to.\n";

our (%max_size);

find(\&large_file, $ARGV[0]);

foreach (sort by_size keys %max_size){
	printf FOUT ("%-70s%10d\n", $_, $max_size{$_});
}

sub by_size{
	my ($sizeA) = $max_size{$a};
	my ($sizeB) = $max_size{$b};

	$sizeB <=> $sizeA;
}

sub large_file{
	return if !stat;

	$max_size{$File::Find::name} = -1 if -d;
	$max_size{$File::Find::dir} = -s if !-d && -s > $max_size{$File::Find::dir};
}

#!/usr/bin/perl -w

#Lab 7, Part 2

use strict;

die "Usage: $0 <integer>" if @ARGV != 1;
my ($int) = shift;
my ($matrix) = [[1,2,3],[4,5,6],[7,8,9]];

print "@{sum_and_mult($matrix, $int)}\n";

sub sum_and_mult{
	my($rlol, $mult) = @_;

	return [map{
		my ($sum) = 0;
		$sum += $_ foreach (@$_);
		$sum *= $mult;
	}@$rlol];
}

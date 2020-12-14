#!/usr/bin/perl

use strict;

use List::Util qw(sum);

die "Usage: $0 <input file>\n" if @ARGV != 1;

$, = "\n";
$\ = "\n";

print getMedian(pullData(@ARGV[0]));

sub pullData{
	
	open(FIN, shift) or return undef;
	my(%hash);
	
	while(<FIN>){
		my ($name, $scores) = split(/:/);
		my (@sets) = map{[split(/\s+/)]} ($scores =~ /\d+\s+\d+\s+\d+/g);
		
		$hash{$name} = (sort{ sum(@$b) <=> sum(@$a) }@sets)[0];
	}

	return \%hash;
}

sub getMedian{
	
	my($rHoL, $row, @results) = shift;
	
	foreach $row (0..2){
		my(@list) = sort{$a <=> $b} map{@{$rHoL->{$_}}[$row]} keys %$rHoL;
		
		my ($odd) = @list % 2;
		my ($mid) = int(@list/2);
		
		push (@results, $odd ? $list[$mid] : ($list[$mid] + $list[$mid - 1])/2);
	}

	return @results;
}
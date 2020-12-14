#!/usr/bin/perl

die "Usage: $0 <input file> <output file>\n" if @ARGV != 2;
open(FIN, "$ARGV[0]") or die "Could not open $ARGV[0] for reading\n";
open(FOUT, ">$ARGV[1]") or die "Could not open $ARGV[1] for writing\n";

@days = (SUN, MON, TUE, WED, THU, FRI, SAT);

while(<FIN>){
	chomp;
	
	($url, $hits) = split (/:/);
	@hits = split (/\s+/, $hits);

	$hoh{$_}{$url} = shift (@hits) foreach (@days);	
}

foreach $day (@days){
	
	print FOUT "$day\n", "-" x length($day), "\n";
	
	@urls = sort{$hoh{$day}{$b} <=> $hoh{$day}{$a}} keys %{$hoh{$day}};
	
	printf FOUT ("%-30s - %d\n", $_, $hoh{$day}{$_}) foreach (@urls);
	
	print FOUT "\n";
}
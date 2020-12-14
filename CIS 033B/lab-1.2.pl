#!/usr/bin/perl

$r = [[35, 54, -1, 55, 56], [87, -1, 67, 29, -1], [77, 66, -1, -1, 100]];

$median = Median($r);

#print "Median = $median\n";

print "Median = " . Median($r) . "\n";

sub Median{
	$rlol = shift;
	@scores  = sort{$a <=> $b} grep{$_ >= 0} map{@$_}  @$rlol;
	
	if(@scores % 2){
		return $scores[(@scores-1)/2];
	}
	else{
		return ($scores[(@scores)/2] + $scores[(@scores/2)-1])/2;
	}
}
#!/usr/bin/perl

use strict;
use DB_File;

my @lines;
my $filename = $ARGV[0];
my $input;

tie (@lines, "DB_File", $filename, O_RDWR, 0777, $DB_RECNO) or die "$!\n";

while((print "Enter Command (", scalar(@lines), " lines):"), ($input = <STDIN>) !~  /^q$/i){
	
	chomp($input);
	my ($command, @args)  = split(/\s+/, $input);
	
	if(($command =~ /^d$/i) && (argValidation(scalar(@lines), 2, \@args))){
			deleteLines(\@lines, \@args);
	}
	
	if(($command =~ /^p$/i) && (argValidation(scalar(@lines), 2, \@args))){
			printLines(\@lines, \@args);
	}
	
	if(($command =~ /^i$/i) && (argValidation(scalar(@lines) + 1, 1, \@args))){
			insertLines(\@lines, @args);
	}
	
	if($command !~ /^[dpi]?$/i){
		print "$command is not a valid command!\n";
	}	
}

sub argValidation{
	my ($maxLine, $numArgsExpected, $r_args) = @_;
	
	if(@$r_args == 0 || @$r_args > $numArgsExpected){
			print "Invalid number of arguments!\n";
			return 0;
	}
	
	foreach (@$r_args){
		if ($_ < 1 || $_ > $maxLine){
			print "$_ is not a valid line number\n";
			return 0;
		}	
		$_--;	
	}
	
	push (@$r_args, @$r_args) if (@$r_args < $numArgsExpected);
	
	return 1;	
}

sub insertLines{
	
	my ($r_lines, $lineNum) = @_;
	my @insert;
	
	while((print "Line to add: "), ($input = <STDIN>) !~  /^\.$/i){
		chomp($input);
		push(@insert, $input);
	}
	
	splice(@$r_lines, $lineNum, 0, @insert);
}

sub deleteLines{
	my ($r_lines, $r_lineNums) = @_;
	
	@$r_lineNums = sort{$a <=> $b} @$r_lineNums;
	
	splice(@$r_lines, $r_lineNums->[0], $r_lineNums->[1] - $r_lineNums->[0] + 1) ;
}

sub printLines{
	my ($lines, $r_lineNums) = @_;
	
	my ($start, $end) = sort{$a <=> $b} @$r_lineNums;
	my ($lineNum) = $start + 1;
	open(MORE, "| more");
	
	foreach (@$lines[$start .. $end]){	
		print MORE "$lineNum: $_\n";
		$lineNum++;
	}
	close MORE;
}
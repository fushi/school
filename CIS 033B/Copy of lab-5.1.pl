#!/usr/bin/perl

use strict;

use Getopt::Std;
use DBI;

my (%opts);
my ($db, $cmd, $query);
my ($data, $state, $city, $precip, $high, $low);

getopts('aduls', \%opts);

my($usage) = "Usage: $0 [-a | -d | -u] source_file\n       $0 -s state_name\n       $0 -l\n";

die $usage if ((scalar keys %opts != 1));
die $usage if ($opts{a} || $opts{d}  || $opts{u} || $opts{s} and @ARGV != 1);
die $usage if ($opts{l} and @ARGV != 0);

$db = DBI->connect("DBI:CSV:f_dir=dbs") or die "Could not connect to DB!\n";

#$cmd = $db->prepare("CREATE TABLE weather (state VARCHAR(20), city VARCHAR(20), precip REAL, high REAL, low REAL)");
#$cmd->execute() or die "Could not create table!\n";

if ($opts{a} || $opts{d} || $opts{u}){
	
	open(FIN, $ARGV[0]) or die "Could not open $ARGV[0] for reading!\n";
	
	while(<FIN>){
		chomp;
		($state, $city, $precip, $high, $low) = split (/:/);
		
		if ($opts{a}){
			if (recordExists($state, $city)){
				print "Will not add duplicate record for $state, $city!\n";
			}
			else{
				$cmd = $db->prepare("INSERT INTO weather (state, city, precip, high, low) VALUES ('$state', '$city', '$precip', '$high', '$low')");
				$cmd->execute() || print "Could not insert $state, $city!\n";
			}
		}
		
		if ($opts{d}){
			if(recordExists($state, $city)){
				$cmd = $db->prepare("DELETE FROM weather WHERE state = '$state' AND city = '$city'");
				$cmd->execute() || print "Could not delete $state, $city!\n";
			}
			else{
				print "Will not delete record for $state, $city: Not Found!\n";
			}
		}
		
		if ($opts{u}){
			if(recordExists($state, $city)){
				$cmd = $db->prepare("UPDATE weather SET precip = '$precip', high = '$high', low = '$low' WHERE state = '$state' AND city = '$city'");
				$cmd->execute() || print "Could not update $state, $city!\n";
			}
			else{
				print "Will not update record for $state, $city: Not Found!\n";
			}
		}
	}
}

if($opts{l}){
	
	$query = $db->prepare("SELECT * FROM weather ORDER BY state, city");
	$query->execute();
	
	printf("%-20s %-15s %-10s %-10s %-10s\n", "State", "City", "Precip.", "Avg High", "Avg Low");
	printf("%-20s %-15s %-10s %-10s %-10s\n", "-" x 5, "-" x 4, "-" x 7, "-" x 8, "-" x 7);
	
	while(($state, $city, $precip, $high, $low) = $query->fetchrow_array()){
		printf("%-20s %-15s %-10.1f %-10.1f %-10.1f\n", $state, $city, $precip, $high, $low);	
	}
}

if($opts{s}){
	my ($search) = $ARGV[0];
	
	$query = $db->prepare("SELECT * FROM weather WHERE upper(state) like upper('$search') ORDER BY city");
	$query->execute();
	
	printf("%-15s %-10s %-10s %-10s\n", "City", "Precip.", "Avg High", "Avg Low");
	printf("%-15s %-10s %-10s %-10s\n", "-" x 4, "-" x 7, "-" x 8, "-" x 7);
	
	while(($state, $city, $precip, $high, $low) = $query->fetchrow_array()){
		printf("%-15s %-10.1f %-10.1f %-10.1f\n", $city, $precip, $high, $low);	
	}	
}

sub recordExists{
	my ($state, $city) = @_;
	
		$query = $db->prepare("SELECT * FROM weather WHERE state = '$state' AND city = '$city'");
		$query->execute();
		
		return $query->fetchrow_array()?1:0;	
}
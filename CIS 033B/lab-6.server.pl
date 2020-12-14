#!/usr/bin/perl

use strict;

use IO::Socket;
use DBI;
use POSIX qw(sys_wait_h);

use constant MAXBYTES => 256;

my ($db, $cmd, $query);
my ($data, $state, $city, $precip, $high, $low);
my ($socket, $pid, $buffer);
our($client);


$db = DBI->connect("DBI:CSV:f_dir=dbs") or die "Could not connect to DB!\n";
$socket = IO::Socket::INET->new(LocalPort => 8080,
													Type => SOCK_STREAM,
													Reuse => 1,
													Listen => 10) or die "Could not open Socket!\n";
													
$SIG{CHLD} = 'reaper';
$SIG{ALRM} = 'alarm';

while(1){
	
	$client = $socket->accept() or next;
	
	die "Bad Fork!\n" if (!defined($pid = fork()));
	
	if ($pid == 0){
		close($socket);
		
		alarm(10);
		$buffer = <$client>;
		alarm (0);
		
		dbInsert($1, $db) if $buffer =~ /^a\s+(.*)$/;
		dbDelete($1, $db) if $buffer =~ /^d\s+(.*)$/;
		dbUpdate($1, $db) if $buffer =~ /^u\s+(.*)$/;
		dbSearch($1, $db) if $buffer =~ /^s\s+(.*)$/;
		dbList($db) if $buffer =~ /^l$/;
		
		print $client ("\nSuccess!\n");
		
		exit(0);
	}
	else{
		close($client);
	}
}

sub dbInsert{
	my ($filename, $db) = @_;
	my (%seen) = %{recordExists()};
	my ($fh) = openFile($filename);
	
	while(<$fh>){
		chomp;
		($state, $city, $precip, $high, $low) = split (/:/);	
			
		if(exists $seen{$state}{$city}){
			alarm (2);
			print $client ("Will not add duplicate record for $state, $city!\n");
			alarm (0);
		}
		else{
			$cmd = $db->prepare("INSERT INTO weather (state, city, precip, high, low)
												VALUES ('$state', '$city', '$precip', '$high', '$low')");
			$cmd->execute() || kill(9, getppid());
			$seen{$state}{$city} = 1;
		}
	}
}

sub dbDelete{
	my ($filename, $db) = @_;
	my (%seen) = %{recordExists()};
	my ($fh) = openFile($filename);
	
	while(<$fh>){
		chomp;
		($state, $city, $precip, $high, $low) = split (/:/);
		
		if(exists $seen{$state}{$city}){
			$cmd = $db->prepare("DELETE FROM weather
												WHERE state = '$state' AND city = '$city'");
			$cmd->execute() || kill(9, getppid());
			delete $seen{$state}{$city};
		}
		else{
			alarm (2);
			print $client ("Will not delete record for $state, $city: Not Found!\n");
			alarm (0);
		}
	}
}

sub dbUpdate{
	my ($filename, $db) = @_;
	my (%seen) = %{recordExists()};
	my ($fh) = openFile($filename);
	
	while(<$fh>){
		chomp;
		($state, $city, $precip, $high, $low) = split (/:/);
		
		if(exists $seen{$state}{$city}){
			$cmd = $db->prepare("UPDATE weather
												SET precip = '$precip', high = '$high', low = '$low'
												WHERE state = '$state' AND city = '$city'");
			$cmd->execute() || kill(9, getppid());
		}
		else{
			alarm (2);
			print $client ("Will not update record for $state, $city: Not Found!\n");
			alarm (0);
		}
	}
}

sub dbList{
	
	my ($db) = shift;
	
	$query = $db->prepare("SELECT * FROM weather ORDER BY state, city");
	$query->execute() || kill(9, getppid());
	
	alarm(2);
	printf $client ("%-20s %-15s %-10s %-10s %-10s\n",
							"State", "City", "Precip.", "Avg High", "Avg Low");
	printf $client ("%-20s %-15s %-10s %-10s %-10s\n",
							"-" x 5, "-" x 4, "-" x 7, "-" x 8, "-" x 7);
	alarm(0);
	
	while(($state, $city, $precip, $high, $low) = $query->fetchrow_array()){
		alarm(2);
		printf $client ( "%-20s %-15s %-10.1f %-10.1f %-10.1f\n",
							$state, $city, $precip, $high, $low);	
	}
	alarm(0);
}

sub dbSearch{
	my ($search, $db) = @_;
	
	$search =~ s/^\s*//;
	$search = join(" ", map {uc($_)} split /\s+/, $search);
	
	$query = $db->prepare("SELECT * FROM weather
										WHERE upper(state) like upper('$search') ORDER BY city");
	$query->execute() || kill(9, getppid());
	
	alarm(2);
	printf $client ("%-15s %-10s %-10s %-10s\n", "City", "Precip.", "Avg High", "Avg Low");
	printf $client ("%-15s %-10s %-10s %-10s\n", "-" x 4, "-" x 7, "-" x 8, "-" x 7);
	alarm(0);
	
	while(($state, $city, $precip, $high, $low) = $query->fetchrow_array()){
		alarm(2);
		printf $client ("%-15s %-10.1f %-10.1f %-10.1f\n", $city, $precip, $high, $low);	
	}
	alarm (0);
}

sub recordExists{
	my ($state, $city) = @_;
	my (%seen);
	
	$query = $db->prepare("SELECT state, city FROM weather");
	$query->execute() || kill(9, getppid());
	
	while(($state, $city) = $query->fetchrow_array){
		$seen{$state}{$city} = 1;
	}

	return \%seen;	
}

sub reaper{

	my ($kidpid);
	
	while(($kidpid = waitpid(-1, WNOHANG)) > 0){
		print "Reaped $kidpid\n";
	}
}

sub alarm{
	print $client "Operation Timed Out! (Server Side)\n";
	exit(1);
}

sub openFile{
	my $filename = shift;
	
	if(!open(FIN, $filename)){
		print $client("Could not open $filename for reading!");
		exit(2);
	}
	
	return *FIN;
}
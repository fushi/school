#!/usr/bin/perl

use strict;

use Getopt::Std;
use IO::Socket;

use constant MAXBYTES => 256;

my (%opts, $message, $buffer);

my ($socket) = IO::Socket::INET->new(PeerAddr => "127.0.0.1",
													PeerPort => 8080,
													Proto => 'tcp',
													Type => SOCK_STREAM) or
													die "Could not open Socket!\n";


$SIG{ALRM} = sub {die "Connection timed out! (Client Side)\n"};

open(MORE, "|more");

getopts('a:d:u:s:l', \%opts);

my($usage) = "Usage: $0 [-a | -d | -u] source_file\n      $0 -s state_name\n       $0 -l\n";

die $usage if (@ARGV != 0 || keys(%opts) != 1);

$buffer = "a $opts{'a'}\n" if $opts{'a'};
$buffer = "d $opts{'d'}\n" if $opts{'d'};
$buffer = "u $opts{'u'}\n" if $opts{'u'};
$buffer = "s $opts{'s'}\n" if $opts{'s'};
$buffer = "l\n" if $opts{'l'};

alarm (2);
print $socket ($buffer);
alarm (0);

foreach (<$socket>){
	alarm (2);
	print MORE;
}
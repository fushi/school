#!/usr/bin/perl -w

#Lab 1, Part 1

$total = 0;

while((print "Enter Part Number and Quantity: "), ($data = <STDIN>) !~  /\s*q(uit)+\s*/i)
{
     next if $data =~ /^\s*$/;

     if ($data !~ /^\s*([a-zA-Z]{2})-?(\d{3})-?(\d{2})\s+(\d+)\s*$/)
     {
          print "Incorrect entry.\n";
	  next;
     }

     $list .= uc($1)."-".$2."-".$3." ".$4."\n";

     $total += $4;
};

print "\n".$list."\nThere were ".$total." items\n" if $total;

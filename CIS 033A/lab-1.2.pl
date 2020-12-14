#!/usr/bin/perl -w

#Lab 1, Part 2

while((print "Enter tokens: "), ($data = <STDIN>) !~  /\s*q(uit)+\s*/i)
{
     next if $data =~ /^\s*$/;

     $token_qty += $data =~ s/(\S+)/$1/g;

     $token_char += $data =~ s/(\S)/$1/g;

};

print "\n$token_qty tokens present. Average ".$token_char/$token_qty." characters per token\n\n";

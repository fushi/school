#!/usr/bin/perl -w

use lib(".");
use Stat;

$pages = [25,32,20,28,15,34,29,30,45,35];
$grade = [69,81,72,75,64,89,84,73,92,86];
$junk  = [7,7,1,4,5,4,7,3,4,6,7,5,4,7,3,4,7,4,3,2,6,4,7];

$pobj  = Stat->new($pages);
$gobj  = Stat->new($grade);

$, = " ";
print $pobj->Mean, "\n";
print $pobj->Median, "\n";
print $pobj->Range, "\n";
printf "%-5.2f\n", $pobj->Variance;
printf "%-5.2f\n", $pobj->StdDev;

print "\n\n";

print $gobj->Mean, "\n";
print $gobj->Median, "\n";
print $gobj->Range, "\n";
printf "%-5.2f\n", $gobj->Variance;
printf "%-5.2f\n\n", $gobj->StdDev;

printf "%-5.2f\n\n", $pobj->R($gobj); 

$jobj = Stat->new($junk);
print $jobj->Mode, "\n\n"; 

$shoesize = [8,9.5,9,11,9,9.5,8.5,9,9,9.5];
$ties     = [10,10,8,15,12,13,16,7,12,4];
$sobj = Stat->new($shoesize);
$tobj = Stat->new($ties);
printf "%-5.2f\n", $sobj->R($tobj);
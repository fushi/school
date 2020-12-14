// File iTunes.h
// Interface for classes
//   iTunesEntry - Single iTune object from the simplified iTunes data file
//   iTunesEntryReader - Used to read and return iTunesEntry objects
// Author: Michael Loceff c 2009

#ifndef ITUNES_H
#define ITUNES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class iTunesEntry
{
public:

private:
   string s_title, s_artist;
   int n_time;

public:
   static const unsigned int MIN_STRING = 1;
   static const unsigned int MAX_STRING = 300;
   static const int MAX_ENTRY_LENGTH = 10000;
   static const int MAX_TIME = 100000;

   iTunesEntry();

   //mutators
   bool SetSTitle(string s_arg);
   bool SetSArtist(string s_arg);
   bool SetNTime(int n_arg);

   // accessors
   string GetSTitle() const { return s_title; }
   string GetSArtist() const { return s_artist; }
   int GetNTime() const { return n_time; }

   // helpers
   static int convertStringToSeconds(string s_to_cnvrt);
   string convertTimeToString() const;

   // comparator tools
   // could use static const int, instead:
private:
   static int n_sort_key;

public:
   static enum { SORT_BY_TITLE, SORT_BY_ARTIST, SORT_BY_TIME } e_sort_type;
   static bool SetNSortType( int which_type );
   bool operator<(const iTunesEntry &other) const;
   bool operator>(const iTunesEntry &other) const;
   bool operator==(const iTunesEntry &other) const;
   bool operator!=(const iTunesEntry &other) const;
   string GetArtistLastName() const;
};

class iTunesEntryReader
{
private:
   vector <iTunesEntry> tunes;
   int num_tunes;
   bool file_open_error;
   string tune_file;
   bool readOneEntry(ifstream &infile, iTunesEntry &tune);
   bool isDataLine(string line);

public:
   iTunesEntryReader(string file_name);
   iTunesEntry &operator[](int k);
   string getFileName() { return tune_file; }
   bool readError() { return file_open_error; }
   int getNumTunes() { return num_tunes; }
};
#endif
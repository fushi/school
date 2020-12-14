// File EBookEntry.h
// Interface for classes
//   EBookEntry - Single ebook object from the Project Gutenberg database
//   EBookEntryReader - Used to read and return EBookEntry objects
// Author: Michael Loceff c 2009

#ifndef EBookEntry_H
#define EBookEntry_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class EBookEntry{
public:

private:
   string s_title, s_creator, s_subject;
   int n_etext_num;

public:
   static const int MIN_STRING = 1;
   static const int MAX_STRING = 300;
   static const int MAX_ENTRY_LENGTH = 10000;
   static const int MAX_ID = 100000L;

   EBookEntry();

   //mutators
   bool SetSTitle(string s_arg);
   bool SetSCreator(string s_arg);
   bool SetSSubject(string s_arg);
   bool SetNEtextNum(int n_arg);

   // accessors
   string GetSTitle() const { return s_title; }
   string GetSCreator() const { return s_creator; }
   string GetSSubject()const { return s_subject; }
   int GetNEtextNum() const { return n_etext_num; }

   // comparator tools
   // could use static const int, instead:
private:
   static int n_sort_key;

public:
   enum { SORT_BY_TITLE, SORT_BY_CREATOR, SORT_BY_SUBJECT, SORT_BY_ID };
   static bool SetNSortType( int which_type );
   bool operator<(const EBookEntry &other) const;
   bool operator>(const EBookEntry &other) const;
   bool operator==(const EBookEntry &other) const;
   bool operator!=(const EBookEntry &other) const;
};

class EBookEntryReader
{
private:
   vector <EBookEntry> books;
   int num_books;
   bool file_open_error;
   string book_file;
   EBookEntry readOneBook(string line);
   bool isDataLine(string line);
   int readIDFromLine(string line);
   string readOneEntry(ifstream &infile, string line);
   string readStringFromEntry(string entry_string, string delimiter);

public:
   EBookEntryReader(string file_name);
   EBookEntry &operator[](int k);
   string getFileName() { return book_file; }
   bool readError() { return file_open_error; }
   int getNumBooks() { return num_books; }

private:
   static int convertToInt(string str_to_cnvrt);
};
#endif
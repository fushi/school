// File EBookEntry.cpp
// Implementation for classes
//   EBookEntry
//   EBookEntryReader
// Author: Michael Loceff c 2009

// reads a file containing lines in the format desribed in
// EBookEntry_FormatKey, and provides a vector-like structure
// (a EBookEntryReader object) filled with EBookEntry objects
// for use by the client

#include "EBookEntry.h"

// EBookEntryReader methods ---------------------------------------------
// reads one string in the above record (all lines of the record
// are assumed to be concatenated into a single line prior to 
// this call surrounded by <pgterms:etext> ... </pgterms:etext> )
// and leaves data in an EBookEntry object for return to client
EBookEntry EBookEntryReader::readOneBook(string entry_string)
{
   EBookEntry book;

   book.SetNEtextNum(readIDFromLine(entry_string));
   book.SetSCreator(readStringFromEntry(entry_string, "<dc:creator"));
   book.SetSTitle(readStringFromEntry(entry_string, "<dc:title"));
   book.SetSSubject(readStringFromEntry(entry_string, "<dc:subject"));

   return book;
}

int EBookEntryReader::readIDFromLine(string line)
{
   unsigned int start_num_pos;
   int num_length;

   start_num_pos = line.find("ID=\"etext") + 9;
   num_length = line.substr(start_num_pos).find( "\"");

   if (start_num_pos < 0 || start_num_pos > EBookEntry::MAX_STRING 
      || num_length < 0 || num_length > 20 )
      return 0;
   else
      return convertToInt(line.substr(start_num_pos, num_length));
}

// looks for a line of the form "<pgterms:etext --- " signifying a
// new record to be read and returns true if found
bool EBookEntryReader::isDataLine(string line)
{
   string s;
   if (line.length() < 15)
      return false;
   
   // check for a line of the form "<pgterms:etext --- "
   
   if (line.substr(0,14) == "<pgterms:etext")
      return true;
   return false;     
 }

string EBookEntryReader::readStringFromEntry
   (string entry_string, string delimiter)
{
   unsigned int start, stop, k;
   string string_after_delimiter;

   if (delimiter.length() < 1 || entry_string.length() < delimiter.length())
      return "(no data found)";

   // first find "<dc:title", e.g.
   start = entry_string.find(delimiter);
   if (start > EBookEntry::MAX_ENTRY_LENGTH)
      return "(no data found)";
   string_after_delimiter = entry_string.substr(start+delimiter.length());

   // we're looking for something line ">A ..." rather than ">< ... "
   for (k = 0; k < string_after_delimiter.length() - 1; k++)
   {
      // rather than using isalpha() we check manually to avoid foreign
      if (string_after_delimiter[k] == '>' 
         &&
         // home made isalpha()
         (
            (string_after_delimiter[k+1]>='a' && string_after_delimiter[k+1] <= 'z')
            ||
            (string_after_delimiter[k+1]>='A' && string_after_delimiter[k+1] <= 'Z')
         )
      )
         break;
   }
   if (k == string_after_delimiter.length() - 1)
      return "(no data found)";

   // we've got the starging position for the raw data
   start = k + 1;
   string_after_delimiter = string_after_delimiter.substr(start); // cut off tags
   stop = string_after_delimiter.find("<");   // by above condition, cannot be 0
   
   return string_after_delimiter.substr(0, stop);
}

EBookEntry &EBookEntryReader::operator[](int k)
{
   static EBookEntry dummy_return;
   if (k < 0 || k >= num_books)
      return dummy_return;
   return books[k];
}

// reads lines from the input stream, concatenating until it finds
// the terminating tag, "</pgterms:etext>".  Result is a single long
// line containing entire record wrapped in 
// "<pgterms:etext> ... </pgterms:etext>" which it returns to client.
// assumes first line containing <pgterms:etext> is already in 
// line parameter - required for call
string EBookEntryReader::readOneEntry(ifstream &infile, string line)
{
   string full_entry = line;
   string next_line;

   while ( !infile.eof() && full_entry.length() < EBookEntry::MAX_ENTRY_LENGTH - 20 )
   {
      getline (infile, next_line);
      full_entry += next_line;
      if (next_line == "</pgterms:etext>")
         break;
   }

   // if we have an unterminated entry, force it to be terminated.
   if (next_line != "</pgterms:etext>")
      full_entry += "</pgterms:etext>";

   return full_entry;
}

// constructor which does entire read operation
EBookEntryReader::EBookEntryReader(string file_name)
{
   string name;
   string line, entry_string;
   EBookEntry book;

   num_books = 0;
   file_open_error = false;
   book_file = "NO FILE NAME PROVIDED";

   if (file_name.length() == 0)
   {
      file_open_error = true;
      return;
   }
   book_file = file_name;

   // open file for reading
   ifstream infile(file_name.c_str());
   if (!infile)
   {
      file_open_error = true;
      return;
   }

   // for each line that starts #. read and add to vector
   num_books = 0;
   while ( !infile.eof() )
   {
      getline (infile, line);
      if (isDataLine(line))
      {
         entry_string = readOneEntry(infile, line); // expands  line to an entry
         // if it is not an English entry, we'll have problems with chars
         if ( entry_string.find( ">en<" ) > EBookEntry::MAX_ENTRY_LENGTH )
            continue;
         book = readOneBook(entry_string);
         books.push_back(book);
         num_books++;
      }
    }
    infile.close();
}

int EBookEntryReader::convertToInt(string str_to_cnvrt)
{
   int ret_int;

   istringstream(str_to_cnvrt) >> ret_int;
   return ret_int;
}
// EBookEntry methods ---------------------------------------------------

// static int initialization
int EBookEntry::n_sort_key = EBookEntry::SORT_BY_CREATOR;

// default constructor
EBookEntry::EBookEntry() 
   : s_title(""), s_creator(""), s_subject(""), n_etext_num(0)
{
}

// mutators
bool EBookEntry::SetSTitle(string s_arg)
{
   if (s_arg.length() < MIN_STRING || s_arg.length() > MAX_STRING)
      return false;
   s_title = s_arg;
   return true;
}
bool EBookEntry::SetSCreator(string s_arg)
{
   if (s_arg.length() < MIN_STRING || s_arg.length() > MAX_STRING)
      return false;
   s_creator = s_arg;
   return true;
}
bool EBookEntry::SetSSubject(string s_arg)
{
   if (s_arg.length() < MIN_STRING || s_arg.length() > MAX_STRING)
      return false;
   s_subject = s_arg;
   return true;
}

bool EBookEntry::SetNEtextNum(int n_arg)
{
   if (n_arg < 1 || n_arg > MAX_ID)
      return false;
   n_etext_num = n_arg;
   return true;
}

bool EBookEntry::SetNSortType( int which_type )
{
   switch (which_type)
   {
   case SORT_BY_TITLE:
   case SORT_BY_CREATOR:
   case SORT_BY_SUBJECT:
   case SORT_BY_ID:
      n_sort_key = which_type;
      return true;
   default:
      return false;
   }
   return true;
}

bool EBookEntry::operator<(const EBookEntry &other) const
{
   switch (n_sort_key)
   {
   case SORT_BY_TITLE:
      return (s_title < other.s_title);
   case SORT_BY_CREATOR:
      return (s_creator < other.s_creator);
   case SORT_BY_SUBJECT:
      return (s_subject < other.s_subject);
   case SORT_BY_ID:
      return (n_etext_num < other.n_etext_num);
   default:
      return false;
   }
   return true;
}

bool EBookEntry::operator>(const EBookEntry &other) const
{
   return (other < *this);
}

bool EBookEntry::operator==(const EBookEntry &other) const
{
   return !(other < *this) && !(*this < other);
}

bool EBookEntry::operator!=(const EBookEntry &other) const
{
   return !(other == *this);
}

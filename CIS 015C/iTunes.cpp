// File iTunes.cpp
// Implementation for classes
//   iTunesEntry
//   iTunesEntryReader
// Author: Michael Loceff c 2009

// reads a file containing lines in the format desribed in
// iTunes_FormatKey, and provides a vector-like structure
// (an iTunesEntryReader object) filled with iTunesEntry objects
// for use by the client

#include "iTunes.h"

// iTunesEntryReader methods ---------------------------------------------
// looks for a line of the form "#" signifying a
// new record to be read and returns true if found
bool iTunesEntryReader::isDataLine(string line)
{
   if (line.length() < 1)
      return false;  
   if (line.compare("#\r") == 0)
   //if(line =="#")
      return true;
   return false;     
 }

iTunesEntry &iTunesEntryReader::operator[](int k)
{
   static iTunesEntry dummy_return;
   if (k < 0 || k >= num_tunes)
      return dummy_return;
   return tunes[k];
}

/* reads 3 lines from the input stream, for example 

Eric Clapton
Pretending
283

*/

bool iTunesEntryReader::readOneEntry(ifstream &infile, iTunesEntry &tune)
{
   string next_line, file_title, file_artist, file_time;
   int n_time;

   if ( !infile.eof() )
      getline (infile, file_artist);
   else
      return false;

   if ( !infile.eof() )
      getline (infile, file_title);
   else
      return false;

   if ( !infile.eof() )
      getline (infile, file_time);
   else
      return false;
   // convert string to int
   istringstream(file_time) >> n_time;

   tune.SetSArtist(file_artist);
   tune.SetSTitle(file_title);
   tune.SetNTime(n_time);

   return true;
}

// constructor which does entire read operation
iTunesEntryReader::iTunesEntryReader(string file_name)
{
   string name;
   string line, entry_string;
   iTunesEntry tune;

   num_tunes = 0;
   file_open_error = false;
   tune_file = "NO FILE NAME PROVIDED";

   if (file_name.length() == 0)
   {
      file_open_error = true;
      return;
   }
   tune_file = file_name;

   // open file for reading
   ifstream infile(file_name.c_str());
   if (!infile){
      file_open_error = true;
      return;
   }

   // for each line that starts #. read and add to vector
   num_tunes = 0;
   while ( !infile.eof() )
   {
      getline (infile, line);
      if (isDataLine(line))
      {
         if ( !readOneEntry(infile, tune) )
         {
            file_open_error = true;
            break;
         }
         tunes.push_back(tune);
         num_tunes++;
      }
    }
    infile.close();
}

// iTunesEntry methods ---------------------------------------------------
int iTunesEntry::n_sort_key = iTunesEntry::SORT_BY_ARTIST;

// default constructor
iTunesEntry::iTunesEntry() 
: s_title(""), s_artist(""), n_time(0)
{
}

// mutators
bool iTunesEntry::SetSTitle(string s_arg)
{
   if (s_arg.length() < MIN_STRING || s_arg.length() > MAX_STRING)
      return false;
   s_title = s_arg;
   return true;
}
bool iTunesEntry::SetSArtist(string s_arg)
{
   if (s_arg.length() < MIN_STRING || s_arg.length() > MAX_STRING)
      return false;
   s_artist = s_arg;
   return true;
}
bool iTunesEntry::SetNTime(int n_arg)
{
   if (n_arg < 0 || n_arg > MAX_TIME)
      return false;
   n_time = n_arg;
   return true;
}


int iTunesEntry::convertStringToSeconds(string s_to_cnvrt)
{
   unsigned int colon_pos;
   int minutes, seconds, length_of_sec_string;

   if (s_to_cnvrt.length() < 1)
      return 0;
   colon_pos = (int) s_to_cnvrt.find_first_of(":");
   if (colon_pos < 0 || colon_pos > iTunesEntry::MAX_STRING)
      return 0;

   istringstream(s_to_cnvrt.substr(0, colon_pos)) >> minutes;
   length_of_sec_string = (int) s_to_cnvrt.length()-1 - colon_pos;
   istringstream(s_to_cnvrt.substr(colon_pos + 1, length_of_sec_string))
      >> seconds;

   return minutes*60 + seconds;
}

string iTunesEntry::convertTimeToString() const
{
   int minutes, seconds;
   ostringstream cnvrt_1, cnvrt_2;
   string ret_string = "", s_seconds, s_minutes;

   minutes = n_time / 60;
   seconds = n_time % 60;

   cnvrt_1 << minutes;
   cnvrt_2 << seconds;

   s_minutes += cnvrt_1.str();
   s_seconds = cnvrt_2.str();

   if (s_seconds.length() < 2)
      s_seconds = "0" + s_seconds;

   return s_minutes + ":" + s_seconds;
}

bool iTunesEntry::SetNSortType( int which_type )
{
   switch (which_type)
   {
   case SORT_BY_TITLE:
   case SORT_BY_ARTIST:
   case SORT_BY_TIME:
      n_sort_key = which_type;
      return true;
   default:
      return false;
   }
   return true;
}

bool iTunesEntry::operator<(const iTunesEntry &other) const
{
   switch (n_sort_key)
   {
   case SORT_BY_TITLE:
      return (s_title < other.s_title);
   case SORT_BY_ARTIST:
      // get last name from string
      // stack the last name before the first - no worries about trailing last
      return 
      (
         GetArtistLastName() + s_artist 
            < 
         other.GetArtistLastName() + other.GetSArtist()
      );
   case SORT_BY_TIME:
      return (n_time < other.n_time);
   default:
      return false;
   }
   return true;
}

bool iTunesEntry::operator>(const iTunesEntry &other) const
{
   return (other < *this);
}

bool iTunesEntry::operator==(const iTunesEntry &other) const
{
   return !(other < *this) && !(*this < other);
}

bool iTunesEntry::operator!=(const iTunesEntry &other) const
{
   return !(other == *this);
}

string iTunesEntry::GetArtistLastName() const
{
   // search for first blank from end of string
   // assume no trailing spaces
   string ret_string;
   int k, length;

   length = (int) s_artist.length();
   if ( length < 1 )
      return "";

   for (k = length-1; k >= 0; k--)
   {
      if (s_artist[k] == ' ')
         break;
   }

   if (k >= length-1 )
      return "";

   return s_artist.substr(k + 1, s_artist.length()-1 - k);
}
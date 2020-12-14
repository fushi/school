package session1;
//Session 1
//
import java.util.*; // The class GregorianCalendar is in this package
import java.sql.*;  // The class Timestamp is in this package
import java.text.*;

// Many real-life applications utilize date conversion routines to
// manipulate date types. This class shows examples on how to work
// with GregorianCalendar and Timestamp.
//
public class DateTimeConverter {

   public static GregorianCalendar convertToGregorianCalendar(Timestamp ts) {
        if (ts == null) 
	    return null;

        long millis = ts.getTime();
        GregorianCalendar cal = new GregorianCalendar();
        cal.setTimeInMillis(millis);

	return cal;
    }

    public static Timestamp convertToTimestamp(GregorianCalendar cal) {
        if (cal == null) 
	      return null; 

        Timestamp ts = new Timestamp(cal.getTimeInMillis());

        return ts;
    }

    // Need to qualify java.util.Date since java.sql also contains a Date class.
    public static java.util.Date convertToDate(long time) {

	java.util.Date date = new java.util.Date();
	date.setTime(time);

	return date;
    }

    public static void main(String [] args) {

	GregorianCalendar gc = 
	    convertToGregorianCalendar(Timestamp.valueOf("2005-04-07 14:30:15"));
	// Prints 3/7/2005
	// The reason for the month being 3 is that in GregorianCalendar, 
   	// January is assigned the value 0.
	System.out.println(gc.get(Calendar.MONTH) + "/" + gc.get(Calendar.DATE) + 
			   "/" + gc.get(Calendar.YEAR));
	System.out.println(gc.getTime());
	// Prints Pacific Standard Time, defaults to the timezone of the machine 
	// I'm running this program.
	TimeZone tz = gc.getTimeZone();
	System.out.println(tz.getDisplayName());

	//Notice we pass 3 (for April), instead of 4, for the month param.
	Timestamp ts = 
	    convertToTimestamp(new GregorianCalendar(1776, 3, 7, 14, 30, 15));
	DateFormat formatter = DateFormat.getDateTimeInstance();
	// Prints Apr 7, 2005 2:30:15 PM
	System.out.println(formatter.format(ts));

	long time = ts.getTime();
	System.out.println(time);
	java.util.Date date = convertToDate(time);
	// Prints Thu Apr 07 14:30:15 PDT 2005
	System.out.println(date.toString());
    }
}

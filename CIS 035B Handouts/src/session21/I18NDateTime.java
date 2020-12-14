package session21;

import javax.jws.WebService;
import javax.xml.ws.Endpoint;

import java.util.*;  // TimeZone class
import java.text.*;  // DateFormat class
import java.awt.*;  // Font class

@WebService

public class I18NDateTime {
  public String getDateTime(String langCode, String countryCode,
		  	    String timeZone){
	GregorianCalendar gc = new GregorianCalendar();
	//
	// tr = language,  TR = country
	// The 2-letter codes can be found in the URL links provided
	// in the API documentation of the Locale class.
	//
	Locale loc = new Locale(langCode, countryCode);
	//
	// getDateTimeInstance(date style, time style, locale)
	// FULL - complete, Saturday, August 6, 2005  for date
	//	 	    9:25:47 AM PDT   for time
	// MEDIUM - shorter, Aug 6, 2005   for date 
	// 		     9:25:47 AM  for time
	// SHORT - even shorter,   8/6/05	for date
	//			   9:25 AM	for time
	//
	DateFormat df = DateFormat.getDateTimeInstance(
	  DateFormat.FULL, DateFormat.FULL, loc);
	TimeZone tz = TimeZone.getTimeZone(timeZone);
	//
	// The TimeZone class has a static String[] getAvailableIDs() that
	// you can use to show you all the timezone ids supported.
	//
	df.setTimeZone(tz);
	//
	// The TimeZone setting for Turkey will produce:
	// 06 Agustos 2005 Cumartesi 16:25:47 GMT
	//
	return df.format(gc.getTime());

  }

public static void main(String[] args) {

      Endpoint.publish(
         "http://localhost:8080/WebServiceExample/i18ndatetime",
         new I18NDateTime());

}
  
}

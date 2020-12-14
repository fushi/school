/**
 * @author John Towler
 * @version 1.0
 * CIS 035B
 * Lab 1
 * Due Date: July 12, 2010
 * Date Submitted: July 12, 2010 
 */

package lab1;

import java.util.*;

public class DateValidator {

	/**
	* Checks if date passed is in the future.
	* @param date Date to be checked.
	* @return Boolean true if the date is in the future,
	* boolean false if not.
	*/

	public boolean isFutureDate(GregorianCalendar date){
		GregorianCalendar now = new GregorianCalendar();
		if(date.after(now)) return true;
		return false;
	}

	/**
	* Checks if date passed is in December.
	* @param date Date to be checked.
	* @return Boolean true if the date is in December,
	* boolean false if not.
	*/

	public boolean isMonthDec(GregorianCalendar date){
		if (date.get(Calendar.MONTH) == 11) return true;
		return false;
	}

	/**
	* Checks if date passed is more than 6 months ago.
	* @param date Date to be checked.
	* @Return Boolean true if the date is more than 6 months ago,
	* boolean false if not.
	*/

	public boolean isLongerThanSixMonths(GregorianCalendar date){
		GregorianCalendar ref = new GregorianCalendar();
		ref.add(Calendar.MONTH, -6);
		if(date.before(ref)) return true;
		return false;
	}
}
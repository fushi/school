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

public class PatientDateVerifier {

	/**
	* Checks if date passed meets the criteria for throwing an exception.
	* @param checkUpDate Date to be checked.
	* @throws CheckDateException if date is in the future,
	* in December, or more than 6 months ago. 
	*/

	public void verifyCheckUpDate(GregorianCalendar checkUpDate)
		throws CheckDateException {
		
		DateValidator dv = new DateValidator();

		if(dv.isFutureDate(checkUpDate))
			throw new CheckDateException(checkUpDate, "Remarks:\n" + 
					"Invalid date: Check-up date is in the future.\n");
		
		if(dv.isMonthDec(checkUpDate))
			throw new CheckDateException(checkUpDate, "Remarks:\n" +
					"Patient needs smallpox vaccination.\n");
		
		if(dv.isLongerThanSixMonths(checkUpDate))
			throw new CheckDateException(checkUpDate, "Remarks:\n" +
					"Check-up date is longer than six months.\n" +
					"Patient needs another checkup.\n");
	}
}
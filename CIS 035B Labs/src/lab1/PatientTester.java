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

/**
 *	Class to test the source in lab1. Instantiates a PatientLogger
 *	object, then passes 5 static patients through the processPatient
 *	method. The log file opened during instantiation is closed before
 *	exiting the program.
 */

public class PatientTester {

	public static void main(String[] args) {
		PatientLogger pl = new PatientLogger();

		pl.processPatient("Flash Gordon",
				new GregorianCalendar(2004, 07, 02, 13, 35));
		pl.processPatient("Wonder Woman",
				new GregorianCalendar(2010, 01, 12, 10, 15));
		pl.processPatient("Robin Hood",
				new GregorianCalendar(2004, 11, 25, 9, 22));
		pl.processPatient("Super Girl",
				new GregorianCalendar(2011, 7, 20, 23, 01));
		pl.processPatient("Captain America",
				new GregorianCalendar(2010, 4, 5, 7, 21));
		
		pl.closeLog();
     }
}
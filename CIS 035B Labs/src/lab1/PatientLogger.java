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
import java.text.*;

public class PatientLogger {

	/**
	* Instantiates a new logger with filename "patient_log.txt" 
	* and instantiates a PatientDateVerifier
	*/

	public PatientLogger(){
		log = new Logger("patient_log.txt");
		pdv = new PatientDateVerifier();
	}

	/**
	* Verifies checkup date. If no exceptions, data is sent to stdout.
	* If exceptions occur, it logs to the logger. 
	* @param checkUpDate Date to be checked.
	*/

	public void processPatient(String patientName,
			GregorianCalendar checkUpDate){
		
		SimpleDateFormat formatter = new SimpleDateFormat(format);
		
		String ln = patientName + " " + formatter.format(checkUpDate.getTime());
		
		try{
			pdv.verifyCheckUpDate(checkUpDate);
			System.out.println(ln);
		}catch(CheckDateException e){
			log.writeLine(ln);
			log.writeLine(e.getMessage());
		}
	}
	
	/**
	 * Closes the log file opened during instantiation
	 * of the PatientLogger.
	 */
	
	public void closeLog(){
		log.closeFile();
	}
	
	private Logger log;
	private PatientDateVerifier pdv;
	String format = "EEE MMM dd HH:mm:ss zzz yyyy";
}
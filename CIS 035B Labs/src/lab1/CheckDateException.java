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
* Custom checked exception class that requires a GregorianCalander object
* reference and allows for a custom message to be sent when it is thrown.
*/

public class CheckDateException extends Exception{

	/**
	* Constructor assigns passed reference and string to instance variables.
	* @param checkDate Date that was used when the exception was thrown.
	* @param msg Message to send when the exception is thrown.
	*/

	public CheckDateException(GregorianCalendar checkDate, String msg){
		date = checkDate;
		message = msg;
	}
	
	/**
	 * Override of toString in Throwable. Returns the toString() of the
	 * java.util.GregorianCalendar object used when the exception was
	 * thrown, concatenated with the message sent when the exception was thrown.
	 * @return A string containing the GregorianCalendar object toString()
	 * and a custom message.
	 */

	public String toString(){
		return date + message;
	}
	
	/**
	 * Returns the custom message set when the exception was thrown.
	 * @return A string containing the message
	 */
	
	public String getMessage(){
		return message;
	}
	
	/**
	 * Returns the GregorianCalander object reference sent
	 * when the exception was thrown.
	 * @return The GregorianCalander object reference
	 */
	
	public GregorianCalendar getDate(){
		return date;
	}

	private GregorianCalendar date;
	private String message;
	private static final long serialVersionUID = -6033759563918859004L;
}

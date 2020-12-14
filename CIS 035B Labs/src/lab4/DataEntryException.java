/**
 * John Towler
 * CIS 035B
 * Lab 4
 * Due Date: August 16, 2010
 * Date Submitted: August 16, 2010
 */

package lab4;

import javax.swing.*;

/**
 * Exception class for handling user input in lab 4.
 * @author John Towler
 * @version 1.0: August 4, 2010
 */

public class DataEntryException extends Exception {

	/**
	 * 
	 * @param parentWindow JFrame that the data was entered in.
	 * @param name Name of the entry field the data was entered in.
	 * @param command Command to give to the exception.
	 */
	public DataEntryException(JFrame parentWindow, String name,
			String command){
		
		this.parentWindow = parentWindow;
		this.name = name;
		this.command = command;

	}
	
	/**
	 * Shows a Message Dialog window, configured by the command given to the
	 * exception given at instantiation.
	 */
	
	public void showErrorWindow(){
		if ("empty".equals(command))
			JOptionPane.showMessageDialog(parentWindow,
					"Please enter a " + name + ".");
	}
	
	String name;
	JFrame parentWindow;
	String command;
	private static final long serialVersionUID = 8421938234241663783L;
}

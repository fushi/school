/**
 * John Towler
 * CIS 035B
 * Lab 4
 * Due Date: August 16, 2010
 * Date Submitted: August 16, 2010
 */

package lab4;

import java.awt.event.*;
import java.util.*;

/**
 * Model class for lab 4. Stores Book references in an ArrayList, and provides
 * methods to add, remove, and retrieve the Book references. Also provides a
 * method for determining how many Books are being held. 
 * @author John Towler
 * @version 1.0: August 4, 2010
 */

public class BooksModel {
	
	/**
	 * Adds a book to booksList.
	 * @param book Book to be added.
	 */
	
	public void addBook (Book book){
		
		booksList.add(book);
		
		ActionEvent ae = new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
		"addb");	
		notifyListeners(ae);
	}
	
	/**
	 * Removes a book to booksList.
	 * @param book Book to be removed.
	 */
	
	public void deleteBook (int index){
		booksList.remove(index);
		ActionEvent ae = new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
				"delb"+index);
		notifyListeners(ae);
	}
	
	/**
	 * 
	 * @return The number of books currently being held by the model.
	 */
	
	public int getNumBooks(){
		return booksList.size();
	}
	
	/**
	 * Retrieves a Book from the model.
	 * @param index Index of the Book to be returned
	 * @return The Book located at the given index. Returns null if there is no
	 * book at the index.
	 */
	
	public Book getBook (int index){
		
		try{
			return booksList.get(index);
		}
		catch(IndexOutOfBoundsException e){
			return null;
		}
	}

	/**
	 * Registers objects as listeners of the ActionEvents created by this model.
	 * @param listener Object that wants to listen.
	 */
	
	public synchronized void addActionListener(ActionListener listener) {

		  if (listenersList == null) {
		       listenersList = new ArrayList<ActionListener>();
		  }
		  if (!listenersList.contains(listener)) {
		     listenersList.add(listener);
		  }
	}	
	
	/**
	 * Notifies all registered listeners that an ActionEvent has occured.
	 * @param ae The ActionEvent that occurred.
	 */
	
	private synchronized void notifyListeners(ActionEvent ae) {
		  for (ActionListener listener: listenersList) {
		     listener.actionPerformed(ae);
		  }
	}
	
	private ArrayList<ActionListener> listenersList;
	private ArrayList<Book> booksList = new ArrayList<Book>();
}

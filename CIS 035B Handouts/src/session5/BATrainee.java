package session5;
//Session 5
//

// This class demonstrates inheritance when the parent class
// contains inner classes.
//
import java.util.*;

public class BATrainee extends BookAuditor{ 

	public int getNumTitles() {

 	  // Because of inheritance, the following line is legal.
	  BookCounter bc = new BookCounter();
	  return bc.getNumTitles();
	} 

	public void processTitles() {
	  setTitles();
	}

	public void listTitles() {
	  ArrayList<String> titles = getTitles(); 
	  Iterator<String> it = titles.iterator();
	  while (it.hasNext()) {
	    System.out.println(it.next().toString());
	  }
	}

	public static void main(String[] args) {

	  BATrainee bat = new BATrainee();
	  bat.processTitles();
	  bat.listTitles();
	  System.out.println(bat.getNumTitles());
	 
	}
}


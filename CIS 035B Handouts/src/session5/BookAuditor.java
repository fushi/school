package session5;
//Session 5
//
import java.util.*;

public class BookAuditor {

	//New in JDK 1.5: arraylist will accept only String references.
	//The compiler gives a warning message with the <type> declaration.
	//
	private ArrayList<String> titles;
	private Hashtable<String, Priceable> prices = 
		             new Hashtable<String, Priceable>();

	public BookAuditor() {

	//New in JDK 1.5: arraylist will accept only String references.
	//
	  titles = new ArrayList<String>();

	}

	//Notice that this inner class is declared private.
	//When this inner class gets compiled, the resulting
	//.class file name is:  BookAuditor$TitleLoader
	//
	private class TitleLoader {

	  private void loadTitles() {
	    // Able to access members of the outer class
	    titles.add("In A Sunburned Country");
	    titles.add("Captain and Commander");
	    titles.add("The King of Torts");
	    titles.add("One Man's Wilderness");

	    System.out.println("Loaded the following titles: \n" +
			       getTitles().toString());
	  }

	}

	// This inner class will be accessible to subclasses of BookAuditor
	//When this inner class gets compiled, the resulting
	//.class file name is:  BookAuditor$BookCounter
	//

	public class BookCounter {
	   private int count;

	   public BookCounter() {
	     count = 0;
	   }

	   public int getNumTitles() {

	     count = titles.size();
	     return count;

	   }
	}

	public void setTitles() {
	  TitleLoader tl = new TitleLoader();
	  tl.loadTitles();
	} 

	public ArrayList<String> getTitles() {
		return titles;
	}

	public void setupPricing(String title, Priceable price) {
	    prices.put(title, price);
	}

	public double getPrice(String title) {
	    Price p = (Price)prices.get(title);
	    return p.getPrice();
	}

}

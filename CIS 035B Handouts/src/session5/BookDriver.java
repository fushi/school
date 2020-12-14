package session5;
// Session 5
//
// This class demonstrates object instantiation 'on the fly' 
// in conjunction with the use of interfaces.
//
import java.util.*;

public class BookDriver {

	public static void main(String[] args) {
	  BookAuditor ba = new BookAuditor();
      ba.setTitles();
      ArrayList<String> titles = ba.getTitles();
      Iterator<String> it = titles.iterator();

	  System.out.println("Setting up pricing for" +
			     " In A Sunburned Country...\n");
	  ba.setupPricing("In A Sunburned Country", 
			new Price() {

			   private double price = 5.60;

			   public double getPrice() {
				return price;
			   }
		        } );

	  System.out.println(ba.getPrice("In A Sunburned Country"));

       /* The following 2 lines will not compile, even if BookCounter is public
	  BookCounter bc = new BookCounter();
	  System.out.println(bc.getNumTitles());
	  */
Priceable p = new Price() {

	   private double price = 10.60;

	   public double getPrice() {
		return price;
	   }
     } ;
     System.out.println(p.getPrice());
	}
}

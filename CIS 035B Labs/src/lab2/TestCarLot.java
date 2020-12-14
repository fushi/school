/**
 * John Towler
 * CIS 035B
 * Lab 2
 * Due Date: July 21, 2010
 * Date Submitted: July 21, 2010
 */

package lab2;

import java.util.*;

/**
 * Test class for lab2.
 * @author John Towler - Wrapper Class and comments.
 * @author Rolly Dimaandal - Main method.
 * @version 1.0: July 20, 2010
 */
public class TestCarLot {
	
	/**
	 * Tests the classes in lab2. A Properties object is created and filled,
	 * then passed to carAssembler. The process is repeated once.
	 * @param args
	 */
    public static void main(String[] args) {
               Properties p = new Properties();
	    CarLotBroker clb = new CarLotBroker();
	    p.put("licenseplate", "4B75324");
	    p.put("licenseplatemethod", "setLicensePlate");
	    p.put("mileage", new Integer(106004));
	    p.put("mileagemethod", "setMileage");
	    p.put("model", "B4000");
	    p.put("modelmethod", "setModel");
	    p.put("color", "green");
	    p.put("colormethod", "setColor");
	    p.put("index", new Integer(1));
	    p.put("pricemethod", "setPrice");
	    p.put("reportmethod", "reportMazdaPickup");
	    clb.carAssembler("doMazdaPickup", p);
	    p = new Properties();
	    p.put("licenseplate", "HondaBB");
	    p.put("licenseplatemethod", "setLicensePlate");
	    p.put("mileage", new Integer(96037));
	    p.put("mileagemethod", "setMileage");
	    p.put("model", "Civic");
	    p.put("modelmethod", "setModel");
	    p.put("color", "black");
	    p.put("colormethod", "setColor");
	    p.put("price", new Double(4824.76));
	    p.put("pricemethod", "setHondaPrice");
	    p.put("reportmethod", "toString");
	    clb.carAssembler("doHondaSedan", p);
    }
}


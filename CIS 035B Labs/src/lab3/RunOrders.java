/**
 * John Towler
 * CIS 035B
 * Lab 3
 * Due Date: August 4, 2010
 * Date Submitted: August 4, 2010
 */

package lab3;

import java.util.*;

/**
 * Test class for lab3. Creates an OrdersMonitor, two ProcessOrders, and two
 * ReportOrders. Three orders are created, then loaded into the OrdersMonitor.
 * The ReportOrders threads are started, and then the ProcessOrders are started.
 * Only one report should be run, and only after a single processing is done.
 * @author John Towler - Wrapper Class and comments.
 * @author Rolly Dimaandal - Main method.
 * @version 1.0: July 21, 2010
 */

public class RunOrders{

	public static void main(String[] args) {
	   OrdersMonitor om = new OrdersMonitor();
	   ProcessOrders po = new ProcessOrders(om);
	   ProcessOrders po2 = new ProcessOrders(om);
	   ReportOrders ro = new ReportOrders(om);
	   ReportOrders ro2 = new ReportOrders(om);
	   Order ord1 = new Order("Wang Lung", "Denim Jacket",
	   		  82.0, 7, 0,
			  new GregorianCalendar(2005, 3, 7, 14, 30, 15));
	   om.loadOrder(ord1);
	   Order ord2 = new Order("Davy Crockett", "Sunglasses",
	   		  32.0, 1, 0,
			  new GregorianCalendar(2005, 5, 21, 1, 21, 5));
	   om.loadOrder(ord2);
	   Order ord3 = new Order("Lazy Boy", "Sofa Bed",
	   		  545.0, 2, 0,
			  new GregorianCalendar(2005, 10, 11, 4, 10, 8));
	   om.loadOrder(ord3);
	   ro.start();
	   ro2.start();
	   po.start();
	   po2.start();
	
	}
}


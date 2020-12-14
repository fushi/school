/**
 * John Towler
 * CIS 035B
 * Lab 3
 * Due Date: August 4, 2010
 * Date Submitted: August 4, 2010
 */

package lab3;

import java.util.*;
import java.text.*;
import pjl.util.*;

/**
 * A utility class to collect orders, process them, and provide a report.
 * @author John Towler
 * @version 1.0: July 21, 2010
 */

public class OrdersMonitor {

	/** Adds given Order to instance HashSet, so long as processOrders() hasn't
	 * completed.
	 * @param order Order to be added to the HashSet
	 */
	public void loadOrder(Order order){
		if (!poAlreadyRun) orders.add(order);
	}
	
	
	/**
	 * Processes orders that are loaded into the OrdersMonitor. A discount of
	 * 15% is given to any order that is 5 or more of an item that costs $75 or
	 * more. This method can only be run once per order monitor.
	 */
	public synchronized void processOrders(){		
		
		if (poAlreadyRun) return;
		Iterator<Order> i = orders.iterator();
		
		while(i.hasNext()){

			Order o = i.next();
			o.setOrderPrice(o.getItemPrice() * o.getOrderQty());

			if(o.getItemPrice() >= 75 && o.getOrderQty() >= 5){
				o.setOrderPrice(o.getOrderPrice() * .85);
			}
		}	
		notifyAll();
		poAlreadyRun = true;
	}
	
	/**
	 * Prints a report containing details of every order loaded into the
	 * OrderMonitor. This method can only be run once per order monitor, and
	 * will wait to run until after processOrders() has been run.
	 */
	
	public synchronized void reportOrders(){
		
		while (!poAlreadyRun){
			try {
				notifyAll();
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		if (roAlreadyRun) return;
		
		Iterator<Order> i = orders.iterator();
		
		while(i.hasNext()){

			Order o = i.next();
			
			SimpleDateFormat f = new SimpleDateFormat(Constants.DATEFORMAT);
			f.format(o.getOrderDate().getTime());	
			
			System.out.println(Join.String("\t", o.getCustName(),
					o.getItemName(), o.getItemPrice(), o.getOrderQty(),
					o.getOrderPrice(), f.format(o.getOrderDate().getTime())));
		}
		notifyAll();
		roAlreadyRun = true;
	}
	
	private HashSet<Order> orders = new HashSet<Order>();
	private boolean poAlreadyRun;
	private boolean roAlreadyRun;
}

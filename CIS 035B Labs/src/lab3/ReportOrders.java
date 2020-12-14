/**
 * John Towler
 * CIS 035B
 * Lab 3
 * Due Date: August 4, 2010
 * Date Submitted: August 4, 2010
 */

package lab3;

/**
 * Thread that takes an OrdersMonitor, and then invokes that OrdersMonitors
 * reportOrders().
 * @author John Towler
 * @version 1.0: July 21, 2010
 */

public class ReportOrders extends Thread {
	
	public ReportOrders(OrdersMonitor om){
		monitor = om;
	}
	
	public void run(){
		monitor.reportOrders();
	}
	private OrdersMonitor monitor;
}

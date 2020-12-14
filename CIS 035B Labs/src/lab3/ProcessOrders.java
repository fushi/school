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
 * processOrders().
 * @author John Towler
 * @version 1.0: July 21, 2010
 */

public class ProcessOrders extends Thread{
	
	public ProcessOrders(OrdersMonitor om){
		monitor = om;
	}
	
	public void run(){
		monitor.processOrders();
	}
	private OrdersMonitor monitor;
}

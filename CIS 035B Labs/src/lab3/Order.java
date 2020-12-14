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
 * Java bean for order information in lab3. 
 * @author John Towler
 * @version 1.0: July 21, 2010
 */

public class Order {
	
	public Order(){
		
	}
	
	/**
	 * Constructor that fills the java bean.
	 * @param custName Customer Name
	 * @param itemName Item Name
	 * @param itemPrice Item Price
	 * @param orderQty Quantity Ordered
	 * @param orderPrice Order Total
	 * @param orderDate Date Ordered
	 */
	public Order(String custName, String itemName, double itemPrice,
			int orderQty, double orderPrice, GregorianCalendar orderDate){
		this.custName = custName;
		this.itemName = itemName;
		this.itemPrice = itemPrice;
		this.orderQty = orderQty;
		this.orderPrice = orderPrice;
		this.orderDate = orderDate;
	}
	
	public String getCustName(){
		return custName;
	}
	public String getItemName(){
		return itemName;
	}
	public double getItemPrice(){
		return itemPrice;
	}
	public int getOrderQty(){
		return orderQty;
	}
	public double getOrderPrice(){
		return orderPrice;
	}
	public GregorianCalendar getOrderDate(){
		return orderDate;
	}
	
	public void setCustName(String custName){
		this.custName = custName;
	}
	public void setItemName(String itemName){
		this.itemName = itemName;
	}
	public void setItemPrice(double itemPrice){
		this.itemPrice = itemPrice;
	}
	public void setOrderQty(int orderQty){
		this.orderQty = orderQty;
	}
	public void setOrderPrice(double orderPrice){
		this.orderPrice = orderPrice;
	}
	public void setOrderDate(GregorianCalendar orderDate){
		this.orderDate = orderDate;
	}
	
	private String custName;
	private String itemName;
	private double itemPrice;
	private int orderQty;
	private double orderPrice;
	private GregorianCalendar orderDate;
}

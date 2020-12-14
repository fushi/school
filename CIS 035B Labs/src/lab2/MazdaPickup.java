/**
 * John Towler
 * CIS 035B
 * Lab 2
 * Due Date: July 21, 2010
 * Date Submitted: July 21, 2010
 */

package lab2;

import pjl.util.Join;

/**
 * Extends lab2.Car, adding a pricing scheme and a reporting method;
 * @author John Towler
 * @version 1.0: July 20, 2010
 */

public class MazdaPickup extends Car {
	
	//Inner class, contains utility method getPrice()
	private class PriceSetter{
		/**
		 * Returns a value from priceArray based on index passed.
		 * @param index Index of the element to return.
		 * @return The integer contained at the given index.
		 */
		public double getPrice(int index){
			return priceArray[index];
		}
		private double[] priceArray = {2500.0, 3784.20, 5780.50};
	}
	
	/**
	 * Sets instance variable price via inner class and array.
	 * @param index Index of the array element to set price to.
	 */
	
	public void setPrice(int index){
		PriceSetter ps = new PriceSetter();		
		price = ps.getPrice(index);
	}
	
	public double getPrice(){
		return price;
	}
	
	/**
	 * Reporting method.
	 * @return A string containing the license plate, model, and price of the
	 * MazdaPickup. 
	 */
	
	public String reportMazdaPickup(){
		return Join.String(" ", getLicensePlate(), getModel(), getPrice());
	}
	
	double price;
}

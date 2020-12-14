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
 * Extends lab2.Car, adding getter/setter methods for hondaPrice instance
 * variable, and overriding toString();
 * @author John Towler
 * @version 1.0: July 20, 2010
 */

public class HondaSedan extends Car {
	
	public double getHondaPrice(){
		return hondaPrice;
	}
	
	public void setHondaPrice(double price){
		hondaPrice = price;
	}
	
	/**
	 * @return A string concatenation of the license plate, mileage, model,
	 * color, and price.
	 */
	public String toString(){
		
		return Join.String(" ", getLicensePlate(), getMileage(), getModel(),
				getColor(), getHondaPrice());
	}
	

	private double hondaPrice;
}

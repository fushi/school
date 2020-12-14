/**
 * John Towler
 * CIS 035B
 * Lab 2
 * Due Date: July 21, 2010
 * Date Submitted: July 21, 2010
 */

package lab2;

/**
 * Java bean, designed to imitate the properties of a real world car.
 * @author John Towler
 * @version 1.0: July 20, 2010
 */

public class Car {
	
	public String getLicensePlate(){
		return licensePlate;
	}
	public int getMileage(){
		return mileage;
	}
	public String getModel(){
		return model;
	}
	public String getColor(){
		return color;
	}
	
	public void setLicensePlate(String licensePlate){
		this.licensePlate = licensePlate;
	}
	public void setMileage(int mileage){
		this.mileage = mileage;
	}
	public void setModel(String model){
		this.model = model;
	}
	public void setColor(String color){
		this.color = color;
	}
	
	private String licensePlate;
	private int mileage;
	private String model;
	private String color;
}
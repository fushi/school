package session7;
//Session 7
//

// Class to store flight information


public final class FlightInfo implements Viewable {
  
  public final static int REG_FLTNUM = 1;
  public final static int SPCL_FLTNUM = 0;

  public int someField = 5;

  private String flightNumber;
  private int gate;
  private int numberOfPassengers; 

  public FlightInfo() {
	flightNumber = null; 
	gate = 0;  // Assume no gate is really numbered 0 
	numberOfPassengers = 0;
  }

  public FlightInfo(String fltNum, int gte, int numPass) {
	flightNumber = fltNum;
	gate = gte;  
	numberOfPassengers = numPass;
  }

  public String getFlightNumber() {
	return flightNumber;
  }

  public String getFlightNumber(int flag) {

	String retval;

	if (flag == SPCL_FLTNUM) 
	    retval = flightNumber.substring(1);
	else
	    retval = flightNumber;

	return retval;
  }

  public int getGate() {
	return gate;
  }

  public int getNumberOfPassengers() {
	return numberOfPassengers;
  }

  public void setFlightNumber(String flightNumber) {
	this.flightNumber = flightNumber;
  }

  public void setGate(int gate) {
	this.gate = gate;
  }

  public void setNumberOfPassengers(int passengers) {
	numberOfPassengers = passengers;
  }

}

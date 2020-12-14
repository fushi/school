package session4;
//Session 4
//

// Singleton class to store flight information.
// A singleton class supports only one instance of itself.


public final class FlightInfo {
  

  private static FlightInfo fi = null;

  private String flightNumber;
  private int gate;
  private int numberOfPassengers; 

  // Notice that the following constructors are not
  // accessible to other/external classes
  //
  private FlightInfo() {
	flightNumber = "UA100"; 
	gate = 1;  
	numberOfPassengers = 100;
  }

  private FlightInfo(String fltNum, int gte, int numPass) {
	flightNumber = fltNum;
	gate = gte;  
	numberOfPassengers = numPass;
  }

  // This static method returns the same FlightInfo object
  // reference every time it gets invoked. 
  //
  public static FlightInfo getInstance() {

	if (fi == null)
	   fi = new FlightInfo();

	return fi;
  }


  // This static method returns the same FlightInfo object
  // reference every time it gets invoked. 
  //
  public static FlightInfo getInstance(String fltNum, int gte, int numPass) {
 
	if (fi == null)
	   fi = new FlightInfo(fltNum, gte, numPass);

	return fi;

  }

  public String getFlightNumber() {
	return flightNumber;
  }


  public int getGate() {
	return gate;
  }

  public int getNumberOfPassengers() {
	return numberOfPassengers;
  }


}

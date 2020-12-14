package session4;
//Session 4
//
public class TestSingleton {
	public static void main(String[] args) {
	   FlightInfo flt1 = FlightInfo.getInstance("AA123", 35, 213);
	   FlightInfo flt2 = FlightInfo.getInstance();
	   //
	   // Test returns true
	   if (flt1 == flt2)
	     System.out.println("flt1 & flt2 are referencing the same object.");

	   FlightTester ft = new FlightTester();
	   FlightInfo flt3 = ft.getFlightInfo();
	   //
	   // Test returns true
	   if (flt2 == flt3)
	     System.out.println("flt2 & flt3 are referencing the same object.");

	   System.out.println(flt3.getFlightNumber()); // Prints AA123

	   
	   FlightInfo flt4 = flt3.getInstance();
	   System.out.println(flt4.getFlightNumber()); // Prints AA123. Why?
	}
}

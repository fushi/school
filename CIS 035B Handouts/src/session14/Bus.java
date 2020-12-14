package session14;
//Session 14
//
public class Bus {

	private int busNumber;
	private String busDriver;
	private String busDestination;


	public Bus() {
	  busNumber = -99;
	  busDriver = null;
	  busDestination = null;
	}

	public Bus(int num, String driver, String dest) {
	  busNumber = num;
	  busDriver = driver;
	  busDestination = dest;
	}

	public void setBusNumber(int num) {
	  busNumber = num;
	}

	public int getBusNumber() {
	  return busNumber;
	}

	public void setBusDriver(String driver) {
	  busDriver = driver;
	}

	public String getBusDriver() {
	  return busDriver;
	}

	public void setBusDestination(String dest) {
	  busDestination = dest;
	}

	public String getBusDestination() {
	  return busDestination;
	}

	public String toString() {
	  return (busNumber + " " + busDriver + " " + busDestination);
	}
}

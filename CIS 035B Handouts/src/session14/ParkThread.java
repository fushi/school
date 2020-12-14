package session14;
//Session 14
//
public class ParkThread extends Thread {

	private Bus bus;
	private BusDispatcher dispatcher;

	public ParkThread(Bus b, BusDispatcher disp) {
	   bus = b;
	   dispatcher = disp;
	}

	//Park a bus when told to do so.
	public void run() {
	   dispatcher.parkBus(bus);
	}
}

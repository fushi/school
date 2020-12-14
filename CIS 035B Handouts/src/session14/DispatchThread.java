package session14;
//Session 14
//
public class DispatchThread extends Thread {

	private BusDispatcher dispatcher;

	public DispatchThread(BusDispatcher disp) {
	   dispatcher = disp;
	}

	public void run() {
	// Get on with the work of dispatching buses
	while(dispatcher.moreBuses()) {
	   // Not trying to be lazy here, but we're in a tight
	   // loop - need to give other threads a chance to do
	   // their work, as well.
	   // 
	   try {
	      sleep(50);
	   }catch (InterruptedException e) {}

	   dispatcher.dispatchBus();
	}
	}
}

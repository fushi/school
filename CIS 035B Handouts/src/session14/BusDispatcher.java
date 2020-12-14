package session14;
//Session 14
//
import java.util.*;

public class BusDispatcher {

	private final int MAX_PARK = 2;

	private Vector<Bus> busStation;
	private Vector<Bus> busStationClone;

	private boolean moreBuses;
	private boolean busesReady = false;

	public BusDispatcher() {

	   busStation = new Vector<Bus>();
	   moreBuses = true;
	}

	public synchronized void parkBus(Bus b) {

	  //Ask thread to wait, if bus station is full
	  //
	  if (busesReady) {
	    try {
	        wait();
	    } catch (InterruptedException ie) {} 
	  }

	  busStation.addElement(b);

	  // Check if bus station is full, clone the busStation Vector
	  // and set the busesReady flag to true. The cloned Vector
	  // will be used by the dispatching thread. This also gives
	  // us the opportunity to clear the busStation Vector.
	  //
	  if (busStation.size() == MAX_PARK) {
	    busStationClone = (Vector<Bus>)busStation.clone();  
	    busStation.clear();
	    busesReady = true;
	  }
	  else
	   busesReady = false;

    	  notifyAll();
	}

	public synchronized void dispatchBus() {

	  //If the busesReady flag is set to false, make the thread
	  //wait. But if there are no more buses to dispatch, then no
	  //point in waiting - just return. In fact, it will be a serious
	  //mistake for the dispatch thread to go in a wait state, if there
	  //are no more buses.
	  //
	  if (!busesReady){
	    if (!moreBuses())
		return;
	    try {
	        wait();
	    } catch (InterruptedException ie) {} 
	  }

	  System.out.println(busStationClone);

	  //Send a signal that buses can be parked, again.
	  busesReady = false;

	  notifyAll();

	} 

	public boolean moreBuses() {
	      return moreBuses;
	}

	public void noMoreBuses() {
	      moreBuses = false;
	}
	    
}

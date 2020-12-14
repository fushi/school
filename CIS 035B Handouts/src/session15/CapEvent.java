package session15;
//Session 15
//
import java.util.*;

// This is a custom event. All custom events have
// EventObject as their super class.
//
public class CapEvent extends EventObject {

	private String state;
	private String cap;

	// The source object triggers a CapEvent. To construct
	// an event, the constructor of EventObject must be
	// invoked passing as parameter the object triggering
	// the event.
	//
	public CapEvent(Object source) {
	    super(source);
	}

	public String getState() {
	    return state;
	}

	public String getCap() {
	    return cap;
	}

	public void setState(String st) {
	    state = st;
	}

	public void setCap(String cp) {
	   cap = cp;
	}
}

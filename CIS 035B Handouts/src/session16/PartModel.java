package session16;
//Session 16
//
import java.awt.event.*;
import java.util.*;

// This class represents the Model in MVC. It notifies all
// registered listeners whenenver a change in partNum occurs.
//
public class PartModel {

	private String partNum;
	private String partName;

	private ArrayList<ActionListener> listenersList;

	public void setPartName(String name){
	   partName = name;
	}

	public String getPartName() {
	   return partName;
	}

	// Create an ActionEvent object. Let all listeners know
	// that an event has occurred.
	//
	public void setPartNum(String num){
	   partNum = num;
	   ActionEvent ae = new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
					    "Partnum");
	   notifyListeners(ae);
	}

	public String getPartNum() {
	   return partNum;
	}

	// Register any qualified ActionListener object.
	//
	public synchronized void addActionListener(ActionListener listener) {

	  if (listenersList == null) {
	       listenersList = new ArrayList<ActionListener>();
	  }
	  if (!listenersList.contains(listener)) {
	     listenersList.add(listener);
	  }
	}

	// Notifying all registered ActionListeners.
	//
	private synchronized void notifyListeners(ActionEvent ae) {
	  for (ActionListener listener: listenersList) {
	     listener.actionPerformed(ae);
	  }
	}

}

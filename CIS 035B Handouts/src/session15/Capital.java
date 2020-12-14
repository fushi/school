package session15;
//Session 15
//
import javax.swing.*;
import java.util.*;
import java.awt.event.*;
import java.io.*;

// This class demonstrates a JFC custom component.
// It generates capitals of US states. This custom component
// triggers CapEvents.
//
public class Capital extends JPanel implements ActionListener{

	//In a real setting, the state-capital entries may be stored
	//in a properties file or even a database table.
	//
	private String[] states = {"Alaska", "California", "New York"};
	private String[] caps = {"Juneau", "Sacramento", "Albany"};
	private JComboBox stateCB = new JComboBox(states);
	private JButton goBtn = new JButton("Go");

	//All registered CapEvent listeneres will be stored in
	//this ArrayList.
	//
	private ArrayList<CapListener> capListeners = new ArrayList<CapListener>();

	//This class generates CapEvents.
	//
	CapEvent capEvent = new CapEvent(this);

	public Capital() {
	   buildPanel();
	}

	public void buildPanel() {
	   add(stateCB);
	   add(goBtn);
	   goBtn.addActionListener(this);
	}

	// When the GO button is clicked, setup the CapEvent.
	// Make sure all registered listeners get the event.
	//
	public void actionPerformed(ActionEvent ae) {
	   String state = (String)stateCB.getSelectedItem();
	   String capital = caps[stateCB.getSelectedIndex()];
	   capEvent.setState(state);
	   capEvent.setCap(capital);
	   processEvent(capEvent);
	}

	//Any listener interested in handling a CapEvent will
	//be registered/stored in this class' ArrayList
	//
	public synchronized void addCapListener(CapListener cl) {

	   if (capListeners.contains(cl))
		return;

	    capListeners.add(cl);
	}

	public synchronized void removeCapListener(CapListener cl) {
	   if (capListeners.contains(cl))
	      capListeners.remove(cl);
	}

	// This method notifies all users that a CapEvent happened.
	// Every listener has a handleCap() method that can be used
	// to pass the CapEvent.
	//
	private void processEvent(CapEvent ce) {

	    ArrayList listClone = (ArrayList)capListeners.clone();

	    synchronized(this) {
	      for(int k = 0; k < capListeners.size(); ++k) {
		CapListener listener = (CapListener)capListeners.get(k);
		listener.handleCap(ce);
	      }
	    }
	}

}

package session15;
//Session 15
//
import javax.swing.*;
import java.util.*;
import java.awt.event.*;

public class CapUser extends JFrame implements CapListener {

	//Using the customized component.
	//
	Capital cap = new Capital();

	public void buildGUI() {

	   getContentPane().add(cap);
	   // This class registers itself as a listener to CapEvents
	   //
	   cap.addCapListener(this);

	   //Dispose this JFrame gracefully when the window is dismissed.
	   //
	   setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	   setSize(200,100);
	   setVisible(true);
	  
	}

	public void handleCap(CapEvent ce) {

	   System.out.println(ce.getCap());
	}

	public static void main(String [] args) {

	   CapUser cu = new CapUser();
	   cu.buildGUI();
	}
}

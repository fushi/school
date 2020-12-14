package session18;
//Session 18
//
import javax.swing.*;
import java.util.*;
import java.text.*;
import java.awt.*;
import java.awt.event.*;

// This program lists the current date & time in the timezone selected,
// using format conventions in the locale selected.

public class TestLocale extends JFrame implements ActionListener {

	Locale[] locs = Locale.getAvailableLocales();
	String[] zones = TimeZone.getAvailableIDs();

	JComboBox localesCB = new JComboBox();
	JComboBox timezonesCB = new JComboBox();

	JLabel timeLabel = new JLabel();

	JPanel mainPanel = new JPanel();

	public void buildGUI() {

	  GridBagLayout gbl = new GridBagLayout();
	  GridBagConstraints gbc = new GridBagConstraints();

	  mainPanel.setLayout(gbl);
	  Insets ins = new Insets(10,10,10,10);
	  gbc.insets = ins;

	  gbc.gridx = 0;
	  gbc.gridy = 0;
	  gbl.setConstraints(localesCB, gbc);
	  loadLocales();
	  mainPanel.add(localesCB);

	  gbc.gridy = 1;
	  gbl.setConstraints(timezonesCB, gbc);
	  loadTimezones();
	  timezonesCB.addActionListener(this);
	  mainPanel.add(timezonesCB);

	  gbc.gridy = 2;
	  gbl.setConstraints(timeLabel, gbc);
	  //This line was added to get Chinese characters to display.
	  //Note that Serif.plain is a font type that is available in
	  //my JDK environment.
	  timeLabel.setFont(new Font("Serif.plain", Font.BOLD, 14));
	  mainPanel.add(timeLabel);

	  getContentPane().add(mainPanel);
	  //Disposes the frame and exits the application gracefully when
	  //the user clicks on the dismiss/close button of the window.
	  setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	  setSize(400,300);
	}

	private void loadLocales() {

	  for (int k = 0; k < locs.length; ++k) {
	     localesCB.addItem(locs[k].getDisplayName() + " " +
	        locs[k].toString());
	  }
	}

	private void loadTimezones() {

	  for (int k = 0; k < zones.length; ++k) {
	     timezonesCB.addItem(zones[k]);
	  }
	}

	public void actionPerformed(ActionEvent ae) {

	  if (ae.getSource() == timezonesCB) {
	    Locale loc = locs[localesCB.getSelectedIndex()];
	    TimeZone tz = TimeZone.getTimeZone((String)timezonesCB.getSelectedItem());
	    Calendar cal = new GregorianCalendar();
	    DateFormat formatter = 
	      DateFormat.getDateTimeInstance (DateFormat.MEDIUM, DateFormat.LONG, loc);
	    formatter.setTimeZone(tz);
	    timeLabel.setText(formatter.format(cal.getTime()));
	  }

	}

	public static void main(String [] args) {
	  TestLocale tl = new TestLocale();
	  tl.buildGUI();
	  tl.setVisible(true);
	}
}

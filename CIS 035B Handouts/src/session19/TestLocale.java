package session19;
//Session 19
//
import javax.swing.*;
import java.util.*;
import java.text.*;
import java.awt.*;
import java.awt.event.*;

// This program lists the current date & time in the timezone selected,
// using format conventions in the locale selected. It also uses a
// resource bundle file to extract the internationalized translations
// of the labels used in the JFrame.
//

public class TestLocale extends JFrame implements ActionListener {

	Locale[] locs = Locale.getAvailableLocales();
	String[] zones = TimeZone.getAvailableIDs();

	JComboBox localesCB = new JComboBox();
	JComboBox timezonesCB = new JComboBox();

	JLabel localeDescLabel = new JLabel();
	JLabel timezoneDescLabel = new JLabel();
	JLabel timeDescLabel = new JLabel();

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
	  gbl.setConstraints(localeDescLabel, gbc);
	  mainPanel.add(localeDescLabel);

	  gbc.gridx = 1;
	  gbl.setConstraints(localesCB, gbc);
	  loadLocales();
	  mainPanel.add(localesCB);

	  gbc.gridx = 0;
	  gbc.gridy = 1;
	  gbl.setConstraints(timezoneDescLabel, gbc);
	  mainPanel.add(timezoneDescLabel);

	  gbc.gridx = 1;
	  gbl.setConstraints(timezonesCB, gbc);
	  loadTimezones();
	  timezonesCB.addActionListener(this);
	  mainPanel.add(timezonesCB);

	  gbc.gridx = 0;
	  gbc.gridy = 2;
	  gbl.setConstraints(timeDescLabel, gbc);
	  mainPanel.add(timeDescLabel);

	  gbc.gridx = 1;
	  gbl.setConstraints(timeLabel, gbc);
	  //This line was added to get Chinese characters to display.
	  //Note that Serif.plain is a font type that is available in
	  //my JDK environment.
	  timeLabel.setFont(new Font("Serif.plain", Font.BOLD, 14));
	  mainPanel.add(timeLabel);

	  localeDescLabel.setFont(new Font("Serif.plain", Font.BOLD, 14));
	  timezoneDescLabel.setFont(new Font("Serif.plain", Font.BOLD, 14));
	  timeDescLabel.setFont(new Font("Serif.plain", Font.BOLD, 14));

	  //Labels_en.properties is the resource bundle file that
	  //contains the internationalized label translations.
	  //
	  setDescLabels("Labels_en");

	  getContentPane().add(mainPanel);
	  //Disposes the frame and exits the application gracefully when
	  //the user clicks on the dismiss/close button of the window.
	  setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	  setSize(400,300);
	}

	// Service method to load the resource bundle translations
	// from the properties file.
	//
	private void setDescLabels(String resource) {

	  ResourceBundle rb = ResourceBundle.getBundle(resource);
	  String localeDesc = (String) rb.getObject("locale");
	  String timezoneDesc = (String) rb.getObject("timezone");
	  String timeDesc = (String) rb.getObject("time");

	  localeDescLabel.setText(localeDesc);
	  timezoneDescLabel.setText(timezoneDesc);
	  timeDescLabel.setText(timeDesc);
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

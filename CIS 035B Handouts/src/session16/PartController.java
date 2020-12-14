package session16;
//Session 16
//
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

// This class represents the controller class in MVC.
// Controller ------> Model --------> View
//
public class PartController extends JFrame implements ActionListener{

	private JButton diskBtn;
	private JButton driveBtn;
	private JTextField partNumFld = new JTextField(20);
	private JPanel partNumPnl = new JPanel();
	private JPanel btnsPnl = new JPanel();
	private JPanel mainPnl = new JPanel();
	 
	private PartModel model;

	public PartController(PartModel mo) {
	  ImageIcon diskIcon = new ImageIcon("disk1.gif");
	  // Put the icon on the button, instead of a label.
	  diskBtn = new JButton(diskIcon);
	  ImageIcon driveIcon = new ImageIcon("drive1.gif");
	  driveBtn = new JButton(driveIcon);

	  model = mo;
	}

	public void buildGUI() {
	   GridBagLayout gbl = new GridBagLayout(); 
	   GridBagConstraints gbc = new GridBagConstraints();
	   mainPnl.setLayout(gbl);

	   partNumPnl.add(partNumFld);
	   gbc.gridx=0;
	   gbc.gridy=0;
	   gbl.setConstraints(partNumPnl, gbc);
	   mainPnl.add(partNumPnl);

	   diskBtn.addActionListener(this);
	   driveBtn.addActionListener(this);
	   btnsPnl.setLayout(new GridLayout(1,2));
	   btnsPnl.add(diskBtn);
	   btnsPnl.add(driveBtn);
	   gbc.gridy=1;
	   gbl.setConstraints(btnsPnl, gbc);
	   mainPnl.add(btnsPnl);

	   getContentPane().add(mainPnl);
	   setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	   setSize(300, 400);
	   setVisible(true);	
	}

	public void actionPerformed(ActionEvent ae) {
	   if(ae.getSource() == diskBtn) {
		model.setPartName("Disk");
	   }
	   else {
		model.setPartName("Hard Drive");
	   }

	   // Will make the model class notify its listeners
	   // that an event has occurred.
	   //
	   model.setPartNum(partNumFld.getText());
	}


	/*
	public static void main(String[] args) {

	  PartController pc = new PartController(new PartModel());
	  pc.buildGUI();
	}
	*/
}

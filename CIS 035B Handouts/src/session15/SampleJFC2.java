package session15;

import javax.swing.*;
import java.awt.*;

public class SampleJFC2 extends JFrame {

    private JTextField fld = new JTextField(10);
    private JLabel lbl = new JLabel("Hello CIS35B");
    private JButton btn = new JButton("Copy");
    private JPanel mainPanel = new JPanel();

    private DefaultListModel model = new DefaultListModel();
    private JList lst = new JList(model);
    private JScrollPane jsp = new JScrollPane(lst);
    private JPanel lstPanel = new JPanel();
    

    public SampleJFC2() {
    }

    public void buildGUI() {
       GridBagConstraints gbc = new GridBagConstraints();
       GridBagLayout gbl = new GridBagLayout();
       mainPanel.setLayout(gbl);
	gbc.gridx=0;
       gbc.gridy=0;
	 jsp.setPreferredSize(new Dimension(100,130));
       lstPanel.add(jsp);
	 gbl.setConstraints(lstPanel,gbc);
       mainPanel.add(jsp);
	 model.addElement("hello");
	 model.addElement("hello2");
       gbc.gridy = 1;
       gbl.setConstraints(fld,gbc);
       mainPanel.add(fld);
       gbc.gridy=2;
       gbl.setConstraints(lbl,gbc);
       mainPanel.add(lbl);
       gbc.gridy=3;
       gbl.setConstraints(btn,gbc);
       mainPanel.add(btn);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(450,450);
       setVisible(true);

    }

    
   public static void main(String[] args) {
	SampleJFC2 sjfc = new SampleJFC2();
	sjfc.buildGUI();
   }
}


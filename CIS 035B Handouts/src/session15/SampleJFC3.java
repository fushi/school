package session15;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.*;

public class SampleJFC3 extends JFrame implements ActionListener, ListSelectionListener{

    private JTextField fld = new JTextField(10);
    private JLabel lbl = new JLabel("Hello CIS35B");
    private JButton btn = new JButton("Copy");
    private JPanel mainPanel = new JPanel();

    private DefaultListModel model = new DefaultListModel();
    private JList lst = new JList(model);
    private JScrollPane jsp = new JScrollPane(lst);
    private JPanel lstPanel = new JPanel();
    

    public SampleJFC3() {
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
       lst.addListSelectionListener(this);
       gbc.gridy = 1;
       gbl.setConstraints(fld,gbc);
       mainPanel.add(fld);
       gbc.gridy=2;
       gbl.setConstraints(lbl,gbc);
       mainPanel.add(lbl);
       gbc.gridy=3;
       gbl.setConstraints(btn,gbc);
       mainPanel.add(btn);
       btn.addActionListener(this);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(450,450);
       setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
	    String str = (String)fld.getText();
	    lbl.setText(str);
    }

    public void valueChanged(ListSelectionEvent lse) {
          lbl.setText((String)lst.getSelectedValue());
    }

   public static void main(String[] args) {
	SampleJFC3 sjfc = new SampleJFC3();
	sjfc.buildGUI();
   }
}


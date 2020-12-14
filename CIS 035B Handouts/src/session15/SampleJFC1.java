package session15;

import javax.swing.*;
import java.awt.*;

public class SampleJFC1 extends JFrame {

    private JTextField fld = new JTextField(10);
    private JLabel lbl = new JLabel("Hello CIS35B");
    private JButton btn = new JButton("Copy");
    private JPanel mainPanel = new JPanel();

    private DefaultListModel model = new DefaultListModel();
    private JList lst = new JList(model);
    private JScrollPane jsp = new JScrollPane(lst);
    private JPanel lstPanel = new JPanel();
    

    public SampleJFC1() {
    }

    public void buildGUI() {
       jsp.setPreferredSize(new Dimension(100,130));
       lstPanel.add(jsp);
	 mainPanel.add(jsp);
	 model.addElement("hello");
	 model.addElement("hello2");
       
       mainPanel.add(fld);
       mainPanel.add(lbl);
       mainPanel.add(btn);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(450,450);
       setVisible(true);

    }

    
   public static void main(String[] args) {
	SampleJFC1 sjfc = new SampleJFC1();
	sjfc.buildGUI();
   }
}


package lab1;

import javax.swing.*;
import javax.swing.table.*;
import java.util.*;
import java.awt.*;

public class MainWindow extends JFrame {
	
	DBProc dbp = new DBProc("/Users/fushi/Dropbox/Workspace/CIS 053 Labs/src/lab1/dbconnection.props");
	
    public final static int ROWS = 200;
    private JTable empTable;
    private JTable deptTable;

    // Column headers for the JTables will be stored in these
    // Vectors
    private Vector<String> empColHeaders = new Vector<String>();
    private Vector<String> deptColHeaders = new Vector<String>();

    // Will be used as Vector of Vectors when constructing
    // JTables
    private Vector empRows = new Vector(); 
    private Vector deptRows = new Vector(); 

    private JPanel mainPanel = new JPanel();
    private JTabbedPane jtp = new JTabbedPane();

    public void buildGUI() {

       GridBagConstraints gbc = new GridBagConstraints();
       GridBagLayout gbl = new GridBagLayout();
       mainPanel.setLayout(gbl);

       // Defining the column headers for the JTables
       empColHeaders.addElement("ID");
       empColHeaders.addElement("First Name");
       empColHeaders.addElement("Last Name");
       empColHeaders.addElement("Salary");
       empColHeaders.addElement("Hire Date");
       empColHeaders.addElement("Department ID");
       
       deptColHeaders.addElement("ID");
       deptColHeaders.addElement("Name");

       empRows = dbp.getEmployees();
       deptRows = dbp.getDepartments();

       //Create the JTables and load them with column headers and
       //rows from Vector of Vectors.
       empTable = new JTable(empRows, empColHeaders);
       deptTable = new JTable(deptRows, deptColHeaders);

       // Put the JTables inside scroll panes
       JScrollPane jsp = new JScrollPane(empTable);
       JScrollPane jsp2 = new JScrollPane(deptTable);

       // Put the scroll panes inside of a tabbed pane. The tabs
       // will be labeled "Books" & "Electronic Books".
       jtp.add(jsp, "Employees");
       jtp.add(jsp2, "Departments");

       gbc.gridx=0;
       gbc.gridy=0;
       gbl.setConstraints(jtp, gbc);
       mainPanel.add(jtp);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(500,500);
    }

    public static void main(String[] args) {
       MainWindow mw = new MainWindow();
       mw.buildGUI();
       mw.setVisible(true);
    }
}

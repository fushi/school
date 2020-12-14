

import javax.swing.*;
import javax.swing.table.*;
import java.util.*;
import java.awt.*;

public class SampleJTables extends JFrame {

    public final static int ROWS = 20;
    private JTable booksTable;
    private JTable booksTable2;

    // Column headers for the JTables will be stored in these
    // Vectors
    private Vector colHeaders = new Vector();
    private Vector colHeaders2 = new Vector();

    // Will be used as Vector of Vectors when constructing
    // JTables
    private Vector rows = new Vector(); 
    private Vector rows2 = new Vector(); 

    private JPanel mainPanel = new JPanel();
    private JTabbedPane jtp = new JTabbedPane();



    public void buildGUI() {
       // Temporary Vectors for rows that will be used in the
       // JTables. These Vectors will be used to create the Vector
       // of Vectors referenced by the variables 'rows' & rows2.
       Vector tempVec = new Vector();
       Vector tempVec2 = new Vector();

       GridBagConstraints gbc = new GridBagConstraints();
       GridBagLayout gbl = new GridBagLayout();
       mainPanel.setLayout(gbl);
       //
       // Defining the column headers for the JTables
       colHeaders.addElement("Title");
       colHeaders.addElement("Author");
       colHeaders2.addElement("Title");
       colHeaders2.addElement("Author");
       colHeaders2.addElement("Store");

       // The example values given here can actually come
       // from a database table.
       tempVec.addElement("The Grapes of Wrath");
       tempVec.addElement("John Steinbeck");

       tempVec2.addElement("Treasure Island");
       tempVec2.addElement("R. L. Stevenson");
       tempVec2.addElement("Kindle store");
       //
       //Adding row to Vector of Vectors
       rows.addElement(tempVec);
       rows2.addElement(tempVec2);

       tempVec = new Vector();
       tempVec.addElement("SAS Survival Guide");
       tempVec.addElement("John Weismann");
       //
       //Adding another row to Vector of Vectors
       rows.addElement(tempVec);

       //Create the JTables and load them with column headers and
       //rows from Vector of Vectors.
       booksTable = new JTable(rows, colHeaders);
       booksTable2 = new JTable(rows2, colHeaders2);
       //
       // Put the JTables inside scroll panes
       JScrollPane jsp = new JScrollPane(booksTable);
       JScrollPane jsp2 = new JScrollPane(booksTable2);

       // Put the scroll panes inside of a tabbed pane. The tabs
       // will be labeled "Books" & "Electronic Books".
       jtp.add(jsp, "Books");
       jtp.add(jsp2, "Electronic Books");


       gbc.gridx=0;
       gbc.gridy=0;
       gbl.setConstraints(jtp, gbc);
       mainPanel.add(jtp);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(500,500);
    }



    public static void main(String[] args) {
       SampleJTables st = new SampleJTables();
       st.buildGUI();
       st.setVisible(true);
    }
}

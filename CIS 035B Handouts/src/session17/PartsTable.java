package session17;
//Session 17
//
import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;

public class PartsTable extends JFrame {

    public final static int ROWS = 20;
    private JTable partsTable;
    //Define the column headers that will be used in the JTable.
    //
    private final String[] colHeaders = {"Part Number", "Part Name",
   				"Part Location"};
    // This class holds the data that is used by the JTable.
    //
    private DefaultTableModel dtm = new DefaultTableModel(colHeaders, ROWS);
    private JButton delBtn = new JButton("Delete");
    private JPanel mainPanel = new JPanel();
    private JPanel tblPanel = new JPanel();
    private JPanel btnPanel = new JPanel();

    public void buildGUI() {
       GridBagConstraints gbc = new GridBagConstraints();
       GridBagLayout gbl = new GridBagLayout();
       mainPanel.setLayout(gbl);
       //Instantiate JTable and let it know about the table model.
       partsTable = new JTable(dtm);
       //'Wrap' the JTable around a scroll pane.
       JScrollPane jsp = new JScrollPane(partsTable);
       Dimension tabDim = new Dimension(400, 110);
       // Even if the table has 20 rows, only a portion of
       // it (as defined by tabDim) will be displayed. The
       // rest of the table will be viewable by scrolling
       // through the scroll pane.
       //
       partsTable.setPreferredScrollableViewportSize(tabDim);
       gbc.gridx=0;
       gbc.gridy=0;
       gbl.setConstraints(jsp, gbc);
       mainPanel.add(jsp);
       //
       // Code below demonstrates the use of an anonymous class.
       // Notice that we did not have to implement the
       // ActionListener interface in this class.
       //
       delBtn.addActionListener(new ActionListener() {
	       public void actionPerformed(ActionEvent ae) {
		       deleteRow();
		}
	});
       gbc.gridy=1;
       gbl.setConstraints(delBtn, gbc);
       mainPanel.add(delBtn);
       getContentPane().add(mainPanel);
       setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       setSize(450,450);
       setVisible(true);
    }

    //Insert a row in the table model.
    public void createRow(int row, Object[] rowVals) {
	    dtm.insertRow(row, rowVals);
    }

    //Delete row from the table model.
    public void deleteRow() {
	    dtm.removeRow(partsTable.getSelectedRow());
    }

    public static void main(String[] args) {
       PartsTable pt = new PartsTable();
       pt.buildGUI();
       pt.createRow(5, new String[] {"5012234", "Disk Drive", "Hawaii"} );
       pt.createRow(1, new String[] {"5013345", "Power Supply", "Ohio"} );
    }
}

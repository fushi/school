/**
 * John Towler
 * CIS 035B
 * Lab 4
 * Due Date: August 16, 2010
 * Date Submitted: August 16, 2010
 */

package lab4;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;

/**
 * View class for lab 4. This class is responsible for generating the table
 * view in a secondary window.
 * @author John Towler
 * @version 1.0: August 4, 2010
 */

public class BooksView extends JFrame implements ActionListener{

	/**
	 * Constructor that registers itself as a listener to events from the model
	 * that this view belongs to. Also sets number of columns equal to 
	 * Constants.ColCount.
	 * @param mo Model that this view belongs to.
	 */
	
	public BooksView(BooksModel mo) {
		model = mo;
		model.addActionListener(this);
		tableModel.setColumnCount(Constants.ColCount);
	}

	/**
	 * Builds then shows a table view of the model.
	 */
	
	public void buildGUI(){	// Need to make sure i don't keep adding panes
		if(!windowBuilt){
		String[] colNames = {"Book ID", "Title", "Author", "Price"};
		tableModel.setColumnIdentifiers(colNames);
		
		JTable table = new JTable(tableModel);
		
		JScrollPane tablePane = new JScrollPane(table);
		
		this.add(tablePane);
		
		this.setSize(new Dimension(400,400));
		
		windowBuilt = true;
		}
		
		setVisible(true);
	}
	
	/**
	 * Performs appropriate actions when ActionEvents occur. Responds to books
	 * being added or deleted from the model.
	 */
	
	public void actionPerformed(ActionEvent ae) {
		if ("addb".equals(ae.getActionCommand())){
			
			Book book = model.getBook(model.getNumBooks()-1);
			
			Object[] props = {book.getId(), book.getTitle(), book.getAuthor(),
					book.getPrice()};
			tableModel.addRow(props);
		}
		
		if ("delb".equals(ae.getActionCommand().substring(0, 4))){			
			tableModel.removeRow(Integer.valueOf(ae.getActionCommand().
					substring(4)));
		}
	}

	private BooksModel model; 
	private DefaultTableModel tableModel = new DefaultTableModel();
	boolean windowBuilt;
	
	private static final long serialVersionUID = -5523401357437873103L;
}

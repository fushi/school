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

/**
 * Controller class for lab 4. Is responsible for generating the main window.
 * @author John Towler
 * @version 1.0: August 4, 2010
 */

public class BooksController extends JFrame implements ActionListener{
	
	/**
	 * Constructor that registers itself as a listener to events from the model
	 * that this view belongs to.
	 * @param mo Model that this controller belongs to.
	 */

	public BooksController(BooksModel mo){

		model = mo;
		model.addActionListener(this);

		view = new BooksView(model);
	}

	/**
	 * 	Builds, then displays, the main window.
	 */
	
	public void buildGUI(){
		GridBagLayout controllerLO = new GridBagLayout();
		this.setLayout(controllerLO);
		
		JPanel textFieldPanel = buildTextFieldPanel();
		JPanel buttonPanel = buildButtonPanel();
		JScrollPane bookScrollPane = buildScrollPane();

		GridBagConstraints gbc = new GridBagConstraints();
		
		gbc.gridx = 0;
		gbc.gridy = 0;
		controllerLO.setConstraints(textFieldPanel, gbc);
		this.add(textFieldPanel);
		
		gbc.gridx = 1;
		gbc.gridy = 0;
		controllerLO.setConstraints(bookScrollPane, gbc);
		bookScrollPane.setPreferredSize(new Dimension(100,150));
		this.add(bookScrollPane);
		
		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = GridBagConstraints.REMAINDER;
		controllerLO.setConstraints(buttonPanel, gbc);
		this.add(buttonPanel);
		
		this.setSize(new Dimension(400,400));
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	/**
	 * Builds the text entry and label panel for Lab 4, main window.
	 * @return A JPanel ready to add to the main JFrame.
	 */
	
	private JPanel buildTextFieldPanel(){
		
		JLabel bookIDJLabel = new JLabel(Constants.bookIDLabel);
		JLabel titleJLabel = new JLabel(Constants.titleLabel);
		JLabel authorJLabel = new JLabel(Constants.authorLabel);
		JLabel priceJLabel = new JLabel(Constants.priceLabel);
		bookIDField = new JTextField(Constants.textFieldLength);
		titleField = new JTextField(Constants.textFieldLength);
		authorField = new JTextField(Constants.textFieldLength);
		priceField = new JTextField(Constants.textFieldLength);
		JPanel textFieldPanel = new JPanel();
		
		GridLayout textFieldLO = new GridLayout(4,2);
		textFieldPanel.setLayout(textFieldLO);
		textFieldPanel.add(bookIDJLabel);
		textFieldPanel.add(bookIDField);
		textFieldPanel.add(titleJLabel);
		textFieldPanel.add(titleField);
		textFieldPanel.add(authorJLabel);
		textFieldPanel.add(authorField);
		textFieldPanel.add(priceJLabel);
		textFieldPanel.add(priceField);
		//textFieldPanel.setPreferredSize(new Dimension(400,400));
		
		return textFieldPanel;
	}

	/**
	 * Builds the button panel for Lab 4, main window. Buttons are given action
	 * commands identical to their instance name, and the parent object is set
	 * to listen to them.
	 * @return A JPanel ready to add to the main JFrame.
	 */
	
	private JPanel buildButtonPanel(){
		
		JPanel buttonPanel = new JPanel();
		
		JButton addButton = new JButton(Constants.addButton);
		JButton delButton = new JButton(Constants.delButton);
		JButton viewButton = new JButton(Constants.viewButton);
		
		addButton.setActionCommand("aButton");
		delButton.setActionCommand("dButton");
		viewButton.setActionCommand("vButton");
		
		GridLayout buttonLO = new GridLayout (1,3);
		buttonPanel.setLayout(buttonLO);
		
		buttonPanel.add(addButton);
		buttonPanel.add(delButton);
		buttonPanel.add(viewButton);
		
		addButton.addActionListener(this);
		delButton.addActionListener(this);
		viewButton.addActionListener(this);
		
		return buttonPanel;
	}

	/**
	 * Builds the scroll pane for Lab 4, main window. 
	 * @return A JScrollPane ready to add to the main JFrame
	 */
	
	private JScrollPane buildScrollPane(){
		
		bookList = new JList(listModel);
		
		JScrollPane bookScrollPane = new JScrollPane(bookList);
		
		return bookScrollPane;
	}
	
	/**
	 * Performs appropriate actions when ActionEvents occur. Responds to
	 * any of the three buttons on the button panel of the main window, as
	 * well as books being added or deleted from the model.
	 */
	
	public void actionPerformed(ActionEvent ae) {
		//System.out.println(ae.getActionCommand());
		
		if ("aButton".equals(ae.getActionCommand())){
			
			String bookID = bookIDField.getText();
			String title = titleField.getText();
			String author = authorField.getText();
			Double price;
			
			try{
				
				checkData(bookID, "Book ID");
				checkData(title, "Title");
				checkData(author, "Author");
				
				price = Double.valueOf(priceField.getText());
				
				model.addBook(new Book(bookID, title, author, price));

				bookIDField.setText(null);
				titleField.setText(null);
				authorField.setText(null);
				priceField.setText(null);
				
			}catch(DataEntryException e){
				e.showErrorWindow();
			}catch(NumberFormatException e){
				JOptionPane.showMessageDialog(this,
					priceField.getText() + " is not a valid price.");
					return;
			}
		}
		if ("dButton".equals(ae.getActionCommand())){
			
			int[] indices = pjl.util.Arrays.Reverse(
					bookList.getSelectedIndices());
			
			for(int n = indices.length - 1; n >= 0; n--){
				model.deleteBook(indices[n]);
			}

		}
		if ("vButton".equals(ae.getActionCommand())){
			view.buildGUI();
		}
		
		if ("addb".equals(ae.getActionCommand())){
			listModel.addElement(model.getBook(model.getNumBooks()-1).getId());
		}
		
		if ("delb".equals(ae.getActionCommand().substring(0, 4))){
			
			int index = Integer.valueOf(ae.getActionCommand().substring(4));
			
			listModel.removeElementAt(index);	
		}
	}
	
	/**
	 * Checks the given object's toString() to ensure it is not empty.
	 * @param obj The return object of a data entry field get method.
	 * @param name Name of entry field that the object comes from.
	 * @throws DataEntryException if obj's toString() method returns "".
	 */
	
	private void checkData(Object obj, String name) throws DataEntryException{
		if ("".equals(obj)) throw new DataEntryException(this, name, "empty");
	}
	
	private BooksView view;
	private BooksModel model;
	
	private JTextField bookIDField;
	private JTextField titleField;
	private JTextField authorField;
	private JTextField priceField;
	
    private DefaultListModel listModel = new DefaultListModel();
    private JList bookList = new JList(listModel);
    
    private static final long serialVersionUID = 5186110372341966158L;
	
	public static void main(String[] args){
		BooksModel bm = new BooksModel();
		BooksController bc = new BooksController(bm);
		bc.buildGUI();
	}
}

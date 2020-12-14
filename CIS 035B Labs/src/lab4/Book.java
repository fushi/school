/**
 * John Towler
 * CIS 035B
 * Lab 4
 * Due Date: August 16, 2010
 * Date Submitted: August 16, 2010
 */

package lab4;

/**
 * Java bean for book information in lab4
 * @author John Towler
 * @version 1.0: August 4, 2010
 */

public class Book {
	
	public Book(){		
	}
	
	public Book(String id, String title, String author, double price){
		this.id = id;
		this.title = title;
		this.author = author;
		this.price = price;
	}

	public String getId(){
		return id;
	}

	public String getTitle(){
		return title;
	}

	public String getAuthor(){
		return author;
	}

	public double getPrice(){
		return price;
	}

	public void setId(String id){
		this.id = id;
	}

	public void setTitle(String title){
		this.title = title;
	}

	public void setAuthor(String author){
		this.author = author;
	}

	public void setPrice(double price){
		this.price = price;
	}
	
	
	private String id;
	private String title;
	private String author;
	private double price;

}

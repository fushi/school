package session3;
// Session 3
//

public class Book {

   private int numPages;
   private String author;
   private String title;
   private String id;

   private int numOnHand;

   public Book() {
	numPages = 0;
	author = null;
	title = null;
	id = null;
   }

   public Book(int pages, String name, String title,
		String bookId) {
	numPages = pages;
	author = name;
	this.title = title;
	id = bookId;
   }

   public String getAuthor(){
	return author;
   }

   public String getTitle(){
	return title;
   }

   public String getId(){
	return id;
   }

   public void setNumOnHand(int num) {
	numOnHand = num;
   }

   public int getNumOnHand() {
	return numOnHand;
   }

   public String toString() {

	return (getTitle());
   }

}



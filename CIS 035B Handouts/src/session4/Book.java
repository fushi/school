package session4;
//Session 4
//
import java.util.*;

// A class that needs to be cloned must implement the
// the empty Cloneable interface.
//
public class Book implements Cloneable {

   private int numPages;
   private String author;
   private String title;
   private String id;

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

   public String toString() {

	return (getTitle());
   }

   // Here, we override the clone() method of the
   // Object class.
   //
   public Object clone() {
     try {
         return super.clone();
     }catch(CloneNotSupportedException ex) {
	 return null;
     }
   }

}

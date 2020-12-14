package session2;
// Session 2
//
import java.io.*;

public class Book implements Serializable{

   private int numPages;
   private String author;
   private String title;
   private String id;

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

   public String toString() {

	return (getTitle());
   }

}



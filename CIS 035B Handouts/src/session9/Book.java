package session9;
//Session 9
//
import java.util.*;

//The Comparable interface contains the compareTo()
//method that takes 2 object references as its parameters.
//The <T> declaration, generic types, allows us to pass
//any object type to the compareTo() method without getting
//compiler warnings.
//
public class Book<T> implements Comparable<T> {

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

   //This method will be used by the TreeMap in the 
   //TreeMapDemo class when putting keys in sequence.
   //
   public int compareTo(T obj) {
	Book bk1 = (Book)obj;
	String title1 = bk1.getTitle();
	String title2 = this.getTitle();
	int result = title2.compareTo(title1);
 	return result;
   }

}



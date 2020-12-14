package session8;
//Session 8
//
import java.util.*;

import session3.Book;

public class LinkedHashSetDemo {


	private LinkedHashSet<Book> linkedHashSet;
	private static Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");

	public LinkedHashSetDemo() {
	   linkedHashSet = new LinkedHashSet<Book>();
	}

	public void setLinkedHashSet() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   linkedHashSet.add(b1);
	   linkedHashSet.add(b2);
	   linkedHashSet.add(b3);
	   //This line will compile, but b1 will not be duplicated
	   linkedHashSet.add(b4);
	}

	public LinkedHashSet getLinkedHashSet() {
	   return linkedHashSet;
	}

	public boolean inSet(Book bk) {
	    if (linkedHashSet.contains(bk))
		return true;
	    else
	        return false;
	}

	public static void main(String [] args){
	    LinkedHashSetDemo s = new LinkedHashSetDemo();
	    s.setLinkedHashSet();
	    LinkedHashSet hs = s.getLinkedHashSet();
	    //The sequence in which the books were loaded will 
	    //be the same sequence when they print.
	    //
	    for (Object book: hs) // This construct of the for loop is new in 1.5.
	      System.out.println(book.toString());
	     
	    System.out.println();

	    //You can also use iterator()
	    Iterator it = hs.iterator();
	    while (it.hasNext()) {
	       Book book = (Book)it.next();
	       System.out.println(book.toString());
	    }

	   Book myBook = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");

	   //Wishful thinking, here.
	   if (s.inSet(myBook))
	      System.out.println("The LinkedHashSet contains my book.");

	   //Yes, this is true.
	   if (s.inSet(b2))
	      System.out.println("The LinkedHashSet contains b2.");

	}
}

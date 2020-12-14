package session8;
//Session 8
//
import java.util.*;

import session3.Book;

public class TreeSetDemo {


	private TreeSet<Book> treeSet;

	public TreeSetDemo() {
	   Comparator<Book> bc = new BookComparator<Book>();
	   treeSet = new TreeSet<Book>(bc);
	}

	public void setTreeSet() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   treeSet.add(b1);
	   treeSet.add(b2);
	   treeSet.add(b3);
	   //This line will compile, but b1 will not be duplicated
	   treeSet.add(b4);
	}

	public TreeSet getTreeSet() {
	   return treeSet;
	}

	public boolean inSet(Book bk) {
	    if (treeSet.contains(bk))
		return true;
	    else
	        return false;
	}

	public static void main(String [] args){
	    TreeSetDemo s = new TreeSetDemo();
	    s.setTreeSet();
	    TreeSet ts = s.getTreeSet();
	    // The books will print in alphabetical order based on
	    // title. BookComparator's compare() method was used. 
	    //
	    for (Object book: ts) // This construct of the for loop is new in 1.5.
	      System.out.println(book.toString());
	     
	    System.out.println();

	    //You can also use iterator()
	    Iterator it = ts.iterator();
	    while (it.hasNext()) {
	       Book book = (Book)it.next();
	       System.out.println(book.toString());
	    }

	   Book myBook = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");

	   // Will find myBook. BookComparator's compare() method
	   // is used to find said book.
	   //
	   if (s.inSet(myBook))
	      System.out.println("The TreeSet contains my book.");

	}
}

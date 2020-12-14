package session9;
//Session 9
//
import java.util.*;

import session3.Book;

public class TreeMapDemo {


	private TreeMap<Book, Book> treeMap;
	//private TreeMap<String, Book> treeMap;

	public TreeMapDemo() {

	   treeMap = new TreeMap<Book, Book>();
	   //treeMap = new TreeMap<String, Book>();
	}

	public void setTreeMap() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   treeMap.put(b1, b1);
	   treeMap.put(b2, b2);
	   treeMap.put(b3, b3);
	   treeMap.put(b4, b4); //Key is not unique, won't be in TreeMap.
	   			//Check out the compare() method in Book.
	}

	public TreeMap getTreeMap() {
	   return treeMap;
	}

	public boolean inMap(Book bk) {
	    // containsValue() checks whether the TreeMap has a
	    // mapping for this book.
	    //
	    if (treeMap.containsValue(bk))
		return true;
	    else
	        return false;
	}

	public static void main(String [] args){
	    TreeMapDemo s = new TreeMapDemo();
	    s.setTreeMap();
	    TreeMap tm = s.getTreeMap();
	    // The books will print in key sequence.
	    //
	    Set entrySet = tm.entrySet();
	    Iterator it = entrySet.iterator();
	    while (it.hasNext()) {
	       System.out.println(it.next());
	    }

	   Book myBook = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");

	   //Wishful thinking, here.
	   if (s.inMap(myBook))
	      System.out.println("The TreeMap contains my book.");

	}
}

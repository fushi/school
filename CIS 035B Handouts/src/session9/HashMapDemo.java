package session9;
//Session 9
//
import java.util.*;

import session3.Book;

public class HashMapDemo {


	private HashMap<String, Book> hashmap;

	public HashMapDemo() {
	   hashmap = new HashMap<String, Book>();
	}

	public void setHashMap() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   hashmap.put("B1", b1);
	   hashmap.put("B2", b2);
	   hashmap.put("B3", b3);
	   hashmap.put("B4", b4);
	}

	public HashMap getHashMap() {
	   return hashmap;
	}

	public Book getBook(String key) {

	   return hashmap.get(key);

	   // No need to cast on Book because the generic type
	   // declarations already stipulate that the HashMap
	   // can only contain Book type object references.

	   // return (Book)hashmap.get(key);
	}

	public static void main(String [] args){
	    HashMapDemo m = new HashMapDemo();
	    m.setHashMap();

	    Book bk = m.getBook("B1");
	    System.out.println(bk.getTitle());

	    bk = m.getBook("B4"); 
	    System.out.println(bk.getTitle());

	    HashMap hm = m.getHashMap();
	    Set entrySet = hm.entrySet();
	    Iterator it = entrySet.iterator();
	    while (it.hasNext()) {
		System.out.println(it.next()); //Prints key-value pair
	    }

	    Set keySet = hm.keySet();
	    it = keySet.iterator();
	    while (it.hasNext()) {
		System.out.println(it.next()); //Prints all keys
	    }
	}
}

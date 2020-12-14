package session9;
//Session 9
//
import java.util.*;

import session3.Book;

public class LinkedHashMapDemo {


	private LinkedHashMap<String, Book> linkedHashMap;

	// 10 - initial size = 10
	// 0.50f - increase map size when 50% of capacity is reached
	// true - load elements in last-accessed order
	// false - load elements in insertion order
	public LinkedHashMapDemo() {
	   linkedHashMap = new LinkedHashMap<String, Book>(10, 0.50f, true);
	}

	public void setLinkedHashMap() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   linkedHashMap.put("B1", b1);
	   linkedHashMap.put("B2", b2);
	   linkedHashMap.put("B3", b3);
	   linkedHashMap.put("B4", b4);
	}

	public LinkedHashMap getLinkedHashMap() {
	   return linkedHashMap;
	}

	public Book getBook(String key) {

	   return linkedHashMap.get(key);

	   // No need to cast on Book because the generic type
	   // declarations already stipulate that the LinkedHashMap
	   // can only contain Book type object references.

	   // return (Book)linkedHashMap.get(key);
	}

	public static void main(String [] args){
	    LinkedHashMapDemo m = new LinkedHashMapDemo();
	    m.setLinkedHashMap();

	    Book bk = m.getBook("B1");
	    System.out.println(bk.getTitle());

	    bk = m.getBook("B4"); 
	    System.out.println(bk.getTitle());

	    LinkedHashMap hm = m.getLinkedHashMap();
	    Set entrySet = hm.entrySet();
	    Iterator it = entrySet.iterator();
	    while (it.hasNext()) {
		System.out.println(it.next()); //Prints key-value pair
	    }				       //in last-accessed order

	    Set keySet = hm.keySet();
	    it = keySet.iterator();
	    while (it.hasNext()) {
		System.out.println(it.next()); //Prints all keys
	    }				       //in last-accessed order
	}
}

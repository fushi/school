package session8;
//Session 8

//


import java.util.*;

import session3.Book;

public class HashSetDemo {


	private HashSet<Book> hashset;

	public HashSetDemo() {
	   hashset = new HashSet<Book>();
	}

	public void setHashSet() {

	   Book b1 = new Book(201, "R. Proenneke",
	     		      "One Man's Wilderness", "B1");
	   Book b2 = new Book(457, "B. Obama",
	     		      "Dreams From My Father", "B2");
	   Book b3 = new Book(398, "D. Richardson", 
			      "In The Company of Soldiers", "B3");
	   Book b4 = b1;

	   hashset.add(b1);
	   hashset.add(b2);
	   hashset.add(b3);
	   //This line will compile, but b1 will not be duplicated
	   hashset.add(b4);
	}

	public HashSet<Book> getHashSet() { //Return type must be HashSet<Book>
	   return hashset;
	}

	public static void main(String [] args){
	    HashSetDemo s = new HashSetDemo();
	    s.setHashSet();
	    HashSet<Book> hs = s.getHashSet();  //Set to Book
	    //The sequence in which the books were loaded may not
	    //be the same sequence when they print.
	    //

	    for (Book book: hs) // This construct of the for loop is new in 1.5.
	      System.out.println(book.toString());
	}
}

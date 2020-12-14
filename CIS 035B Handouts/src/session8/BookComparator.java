package session8;
//Session 8
//
import java.util.Comparator;

import session3.Book;

public class BookComparator<T> implements Comparator<T>{

//This method will be used by the TreeSet class

   public int compare(T obj1, T obj2) {
        Book bk1 = (Book)obj1;
	Book bk2 = (Book)obj2;
	String title1 = bk1.getTitle();
	String title2 = bk2.getTitle();

	int result = title1.compareTo(title2);
	 return result;
   }

//No need to implement equals() as it is already inherited
//and implemented in the Object class.

}

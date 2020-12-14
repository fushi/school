package session10;
//Session 10
//
import java.util.*;

public class CollectionsDemo {

	private ArrayList<String> arrayList;

	public CollectionsDemo() {
	    arrayList = null;
	}

	public void loadArrayList() {
	    List<String> list = Collections.nCopies(5, "Hello");
	    arrayList = new ArrayList<String>(list);
	}

	public void showArrayList() {
	    System.out.println(arrayList);
	}

	public void addElement(int idx, String el) {
	    arrayList.add(idx, el);
	}

	// Notice the generic type declaration. The sort()
	// method in the Collections class needs to know what type
	// of objects it is sorting. This avoids getting a
	// warning from the compiler.
	//
	public List<String> getArrayList() {
	    return arrayList;
	}

	public static void main(String[] args) {

	   CollectionsDemo cd = new CollectionsDemo();
	   cd.loadArrayList();
	   cd.showArrayList();

	   cd.addElement(3, "Adios");
	   cd.showArrayList();

	   // This line will get a warning from the compiler,
	   // if the generic type declaration in getArrayList()
	   // is omitted.
	   //
	   Collections.sort(cd.getArrayList());
	   cd.showArrayList();

	   int result = Collections.binarySearch(cd.getArrayList(), "Adios");
	   System.out.println ("The string is at index: " + result);

	   result = Collections.binarySearch(cd.getArrayList(), "Hello");
	   //
	   //This prints 2. Why?
	   System.out.println ("The string is at index: " + result);
	   //
	   // This prints -2. Why?
	   result = Collections.binarySearch(cd.getArrayList(), "Goodbye");
	   System.out.println ("The string is at index: " + result);

	} 
}

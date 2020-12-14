package session10;
//Session 10
//
import java.util.*;

// This class uses the Arrays class to manipulate an array.
//
public class ArraysDemo {

	private  String[] array;

	public ArraysDemo() {
	    array = new String[10];
	}

	public void loadArray() {
	    // Fill the array with "Hello" from the 6th to the
	    // 9th element.
	    //
	    Arrays.fill(array, 5, 9, "Hello");
	}

	public void showArray() {
	    for  (String val: array)
	       System.out.print(val + " ");

	    System.out.println("\n");
	}

	public void addElement(int idx, String el) {
	    array[idx] = el;
	}

	public String[] getArray() {
	    return array;
	}

	public static void main(String[] args) {

	   ArraysDemo ad = new ArraysDemo();
	   ad.loadArray();
	   ad.showArray();

	   ad.addElement(9, "Adios");
	   ad.showArray();

	   Arrays.fill(ad.getArray(), 0, 5, "Seeya");
	   ad.showArray();
	   Arrays.sort(ad.getArray());
	   ad.showArray();


	} 
}

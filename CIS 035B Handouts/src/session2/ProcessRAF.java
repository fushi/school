package session2;
// Session 2
//
import java.io.*;
import java.util.*;

public class ProcessRAF {
 
	//This method inserts a line after the given lineNum.
	//If this is a new file, the line is inserted at the beginning
	//of the file.
	public void insertLine(String newLine, int lineNum, RandomAccessFile raf) {

	   ArrayList<String> lines = new ArrayList<String>();

	   //Read all lines up to the line desired. This positions the file
	   //pointer to the line right where we want to insert our new line.
	   try{
	     for (int lineCounter = 0; lineCounter < lineNum; ++lineCounter) {
	        raf.readLine();
	     }

	     //Save the value of this file pointer. We'll use it later.
	     //
	     long prevFP = raf.getFilePointer();
	     boolean eof = false;
	     //Now save all the lines from here on to the end of file.
	     //
	     while (!eof) {
	       String line = raf.readLine();
	       if (line != null)
	          lines.add(line);
	       else 
	          eof = true;
	     }

	     //Set the filepointer where we want to insert the line. 
	     raf.seek(prevFP);
	     raf.writeBytes(newLine); //This wipes out the line that's here,
	     			      //if any. No worries, we saved it
				      //already in the ArrayList with the
				      //rest of the lines.

	     // Now go in a loop and write the rest of the lines.
	     Iterator it = lines.iterator();
	     while(it.hasNext()) {
	       raf.writeBytes((String)it.next() + "\n");
	     }
	   
	     raf.close();
	   } catch (IOException e) {e.printStackTrace();}


	}

	public static void main(String[] args) {
	   ProcessRAF praf = new ProcessRAF();
	   RandomAccessFile raf = null;
	   System.out.println("starting...");
	   try {
	      raf = new RandomAccessFile("session2\\raf.txt", "rw");
	   }catch (IOException e) {e.printStackTrace();}

	   praf.insertLine("eat what?\n", 4, raf);
	}
	
}

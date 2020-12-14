package session2;
//Session 2
//
import java.io.*;
import java.util.*;



// This class demonstrates the creation and retrieval
// of a persistent(serialized object)
//
public class SerialDemo {

	private Properties props;

	public SerialDemo() {
	    props = new Properties();
	}

	public void persistBook() {
	  try {
		FileInputStream propsData = 
			new FileInputStream("session2\\book.properties");
		  props.load(propsData);
		  propsData.close();
		} catch (IOException e) {
		  e.printStackTrace();
	  }

	  String title = props.getProperty("title");
	  String author = props.getProperty("author");
	  String pages = props.getProperty("pages");
	  String id = props.getProperty("id");

	  // Notice that bk is a local Book reference. The Book
	  // object being referenced by bk will be garbage collected
	  // as soon as we exit this method.
	  //
	  Book bk = new Book(Integer.parseInt(pages), author,
	  		     title, id);
	  // Attempting to persist the Book object. All objects being
	  // persisted must implement the Serializable interface.
	  //
	  try {
	    // The persisted Book object will be saved in the binary
	    // file book.obj (you can also give the full directory 
	    // path, if you like).
	    //
	    FileOutputStream outFile = new FileOutputStream("session2\\book.obj");
	    ObjectOutputStream outStream = new ObjectOutputStream(outFile);

	    outStream.writeObject(bk);

	  }catch (IOException ex) {
	     ex.printStackTrace();
	  }
	}

	public void showPersistedBook() {

	   Book bk = null;
	   try {
	     FileInputStream inFile = 
	        new FileInputStream("session2\\book.obj");
	     ObjectInputStream inStream = new ObjectInputStream(inFile);

	     bk = (Book) inStream.readObject();
	   } catch (Exception e) {
	     e.printStackTrace();
	   }

	   if (bk != null)
	     System.out.println(bk);
	}

	public static void main(String [] args) {
	    SerialDemo sd = new SerialDemo();
	    sd.persistBook();
	    sd.showPersistedBook();
	}

}

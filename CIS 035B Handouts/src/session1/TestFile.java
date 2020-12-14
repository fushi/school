package session1;
// Session 1
//
// This example was taken from Intro to Java Programming by Liang.
//
import java.io.*;
import java.util.*;

public class TestFile {
  public static void main(String[] args) {
	
    // Create a File object. Path defined is a relative path.
    File file = new File(".", "subdir" + File.separator + "hello.txt");
    System.out.println("Does it exist? " + file.exists());
    System.out.println("Can it be read? " + file.canRead());
    System.out.println("Can it be written? " + file.canWrite());
    System.out.println("Is it a directory? " + file.isDirectory());
    System.out.println("Is it a file? " + file.isFile());
    //Prints false
    System.out.println("Is it absolute? " + file.isAbsolute());
    System.out.println("Is it hidden? " + file.isHidden());

    //Shows redundant .'s in the path.
    System.out.println("What is its absolute path? " +
      file.getAbsolutePath());

    //Like absolute path without redundant .'s.
    try {
      System.out.println("What is its canonical path? " +
        file.getCanonicalPath());
    }
    catch (IOException ex) { }

    System.out.println("What is its name? " + file.getName());
    //Prints the path as defined during instantiation of the File class.
    System.out.println("What is its path? " + file.getPath());

    //lastModified() returns a long value representing the date and time
    // when the file was last modified. The value is in milliseconds
    // measured from 1/1/1970 to last modified date/time.
    System.out.println("When was it last modified? " +
      new Date(file.lastModified()));

    // Character representation of the path-list separator that's used
    // when multiple file paths are given in said path-list.
    System.out.println("What is the path separator? " +
      File.pathSeparatorChar);

    // Character representation of the separator used in a given
    // file path.
    System.out.println("What is the name separator? " +
      File.separatorChar);
  }
}

/**
 * @author John Towler
 * @version 1.0
 * CIS 035B
 * Lab 1
 * Due Date: July 12, 2010
 * Date Submitted: July 12, 2010
 */

package lab1;

import java.io.*;

public class Logger{

	/**
	* Opens a default file, "default.txt", in rw mode
	*/

	public Logger(){
		try{
			raf = new RandomAccessFile("default.txt", "rw");
		}catch(FileNotFoundException e){
			System.out.println(e);
		}
	}

	/**
	* Opens a file using fileName as the filename, in rw mode.
	* @param fileName name of file to open.
	*/

	public Logger(String fileName){
		try{
			raf = new RandomAccessFile(fileName, "rw");
		}catch(FileNotFoundException e){
			System.out.println(e);
		}
	}

	/**
	* Appends a line to the logger.
	* @param line Line to append.
	*/

	public void writeLine(String line){
		try{
			raf.seek(raf.length());
			raf.writeBytes("\n" + line);
		}catch (IOException e){
			System.out.println(e);
		}
	}
	
	/**
	 * Closes the random access file.
	 */
	
	public void closeFile(){
		try{
			raf.close();
		}catch(IOException e){
			System.out.println(e);
		}
	}

	private RandomAccessFile raf;
}

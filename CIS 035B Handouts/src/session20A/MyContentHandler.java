package session20A;

import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.Attributes;
import java.util.*;

public class MyContentHandler extends DefaultHandler {

	private String startTag = null;

	// Parser calls this method when it starts parsing.
	public void startDocument() {
	  System.out.println("Starting document...");
	}

	// This method gets called every time the parser
	// encounters a start tag in the XML file.
	public void startElement(String url, String localName,
				 String qualName, Attributes attribs) {

		startTag = qualName;
	}

	// This method gets called one or more times(depending on
	// parser being used) whenever data is encountered between
	// a start tag and its ending tag.
	public void characters (char[] charArray, int start, int length) {
		String entry = new String(charArray, start, length);
		if (startTag.equals("emp_id")) {
		   System.out.println("Emp ID: " + entry);
		   startTag ="";
		}
		else
		   if (startTag.equals("emp_firstname")) {
		      System.out.println("Emp Firstname: " + entry);
		      startTag ="";
		   }
		else
		   if (startTag.equals("emp_lastname")) {
		      System.out.println("Emp Lastname: " + entry);
		      startTag ="";
		   }

	}


	// Gets called when an end tag is encountered. 
	public void endElement(String url, String localName,
				 String qualName) {
	}

	public void endDocument() {

	  System.out.println("End of document.");
	}
}

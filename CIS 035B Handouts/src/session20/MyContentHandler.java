package session20;
//Session 20
//
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

		System.out.println("Qual name: " + qualName);

		for (int idx=0; idx < attribs.getLength(); ++idx) {
		  System.out.print(attribs.getQName(idx) + "=");
		  System.out.println(attribs.getValue(idx));
		}
	}

	// This method gets called one or more times(depending on
	// parser being used) whenever data is encountered between
	// a start tag and its ending tag.
	public void characters (char[] charArray, int start, int length) {
		String entry = new String(charArray, start, length);
		entry = entry.replaceAll("\n", "[cr]");
		entry = entry.replaceAll(" ", "[space]");
		entry = entry.replaceAll("\t", "[tab]");
		if (startTag.equals("Veg")) {
		   System.out.println("This vegetable is: " + entry);
		   startTag ="";
		}
		else
		   System.out.println(entry);

	}


	// Gets called when an end tag is encountered. 
	public void endElement(String url, String localName,
				 String qualName) {
		System.out.print("End tag: ");
		System.out.println("Qual name: " + qualName);
	}

	public void endDocument() {

	  System.out.println("End of document.");
	}
}

// SAX - Simple API for XML.
package session20A;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.XMLReader;
import org.xml.sax.SAXException;

import java.io.*;

public class CallSAX {

	public static void main(String[] args) 
			throws SAXException,
			ParserConfigurationException,
			IOException {

	  // Get an instance of of the SAX parser factory. This
	  // will choose a parser that's available on your system.
	  // If you want to handpick your own parser, replace the
	  // following three lines with:
	  // XMLReader xmlReader = 
	  //    XMLReaderFactory.createXMLReader("<class name of parser>");
	  //
	  SAXParserFactory factory = SAXParserFactory.newInstance();
	  SAXParser saxParser = factory.newSAXParser();
	  XMLReader xmlReader = saxParser.getXMLReader();
	  
	  // MyContentHandler has the callback methods that the
	  // SAX parser will use.
	  xmlReader.setContentHandler(new MyContentHandler());

	  // - The File constructor finds the XML file on your hard drive.
	  //   In this example, the XML file is passed as a command line
	  //   argument.
	  // - The method toURL() represents the XML file as a Web-ready
	  //   resource - something parsers like to have.
	  // - The abstracted URL is converted to String and gets fed
	  //   to the parser.
	  xmlReader.parse(new File(args[0]).toURL().toString());
	}
}

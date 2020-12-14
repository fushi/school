package session18;
//Session 18
//
import java.awt.*;
import java.util.*;

// The following program lists all available fonts that support
// Chinese characters in a particular JDK environment.
// Here's how I configured my Windows XP machine to support
// Asian characters:
// start -> Control Panel -> Regional and Language Options ->
// Languages -> Install files for East Asian languages

public class ChinaFonts {

  public static void main(String[] args) {
	Vector<Object> chinesefonts = new Vector<Object>();
	Font[] allfonts =
        	GraphicsEnvironment.getLocalGraphicsEnvironment().getAllFonts();
	int fontcount = 0;
	//String chinesesample = "\u4e00";
	String chinesesample = "\u984d";
	for (int j = 0; j < allfonts.length; j++) {
	  //System.out.println(allfonts[j].getFontName());
	    if (allfonts[j].canDisplayUpTo(chinesesample) == -1) { 
	        chinesefonts.add(allfonts[j].getFontName());
	    }
  	    fontcount++;
	}
	System.out.println(chinesefonts);
  }
}

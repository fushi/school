/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package finalpkg;

import java.io.*;


public class fileappend {
    static public void append (String fname, String foo) throws java.io.IOException {

        File file = new File(fname);
        FileWriter writer = new java.io.FileWriter(file);
        writer.append(foo);
    }
}

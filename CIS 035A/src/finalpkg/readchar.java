/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package finalpkg;

import java.io.*;

public class readchar {

    static public int count(DataInputStream stream, char c) throws java.io.IOException{

        int count = 0;

        while(stream.available() != 0){
            if (stream.readChar() == c) count ++;
        }
        return count;
    }
}

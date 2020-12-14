/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package finalpkg;

/**
 *
 * @author John
 */
public class person {
    
    public person(String[] data){
        fname = data[0];
        lname = data[1];
        ssn = data[2];
        num1 = Integer.parseInt(data[3]);
        num2 = Integer.parseInt(data[4]);
        num3 = Integer.parseInt(data[5]);
        num4 = Integer.parseInt(data[6]);
    }

    public String fname;
    public String lname;
    public String ssn;
    public int num1;
    public int num2;
    public int num3;
    public int num4;
}

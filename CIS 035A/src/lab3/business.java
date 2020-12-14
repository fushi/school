/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 3
 * Due Date: Feb 4, 2010
 * Date Submitted: Jan 26, 2010
 */

package lab3;

import java.util.Locale;

/**
 * Lab 3 for CIS 035A, Section 63Z
 * @author John Towler
 * @version 1.0
 */
public class business{

    //Constructors
    public business(){
        name = "Default";
        address = "123 Anystreet Way";
        city = "MyTown";
        state = "Illinois";
        zipcode = 94054;
        creation = new java.util.GregorianCalendar();

        System.out.printf("%-10s%-20s%-10s%-10s%5d\n", name, address, city, state, zipcode);
        System.out.printf("%3s%3d, %4d\n\n", creation.getDisplayName(creation.MONTH, creation.SHORT, Locale.US), creation.get(creation.DATE), creation.get(creation.YEAR));
    }

    /**
     * @param n Name of the business.
     * @param a Address of the business.
     * @param c City of the business.
     * @param s State of the business.
     * @param z Zipcode of the business.
     */
    public business(String n, String a, String c, String s, int z){
        name = n;
        address = a;
        city = c;
        state = s;
        zipcode = z;
        creation = new java.util.GregorianCalendar();

        System.out.printf("%-10s%-20s%-10s%-10s%5d\n", name, address, city, state, zipcode);
        System.out.printf("%3s%3d, %4d\n\n", creation.getDisplayName(creation.MONTH, creation.SHORT, Locale.US), creation.get(creation.DATE), creation.get(creation.YEAR));
    }

    //Methods

    //Fields
    private String name;
    private String address;
    private String city;
    private String state;
    private int zipcode;
    private java.util.GregorianCalendar creation;
}

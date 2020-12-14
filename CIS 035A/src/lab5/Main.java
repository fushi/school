/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 5
 * Due Date: Mar 19, 2010
 * Date Submitted: Mar 19, 2010
 */

package lab5;

/**
 * @author John Towler
 * This package is the driver code for CIS 035A Lab 5.
 * If the other classes were to be integrated into a fully
 * functioning system, this would contain a menu of all flights
 * and options for adding/removing flights, choosing a flight to
 * edit, and exiting the program entirely.
 */
public class Main {

    /**
     * @param
     */
    public static void main(String[] args) {
        flight foo = new flight(10,4);
        
        foo.menu();

    }

}

/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 3
 * Due Date: Feb 4, 2010
 * Date Submitted: Jan 26, 2010
 */

package lab3;

/**
 * Lab 3 for CIS 035A, Section 63Z
 * @author John Towler
 * @version 1.0
 */

public class lab3 {
    public static void main(String[] args) {
        //business bus_test = new business();

        System.out.printf("About to create a business[]\n\n");
        business[] business_array = new business[5];
        System.out.printf("business[] has been created.\n\n");

        array_fill(business_array);
    }
    
    static void array_fill(business[] array){
        int i = 1;
        for(business element : array){
            if(i%4 == 0) element = new business("Foobar", "789 My Street", "Los Gatos", "CA", 95030);
            else element = new business();
            i++;
        }
    }

}
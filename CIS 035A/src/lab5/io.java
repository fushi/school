/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 5
 * Due Date: Mar 19, 2010
 * Date Submitted: Mar 19, 2010
 */

package lab5;
import java.util.*;

/**
 *
 * @author John
 */
public class io {
    static int readInt(String msg){
        Scanner in = new Scanner(System.in);
        while(true){
            try{
                System.out.print(msg);
                return Integer.parseInt(in.nextLine());
            }
            catch(NumberFormatException e){
                System.out.println("Not a valid number. Please try again.");
            }
        }
    }

    static String readString(String msg){
        Scanner in = new Scanner(System.in);
        System.out.print(msg);
        return in.nextLine();
    }
}

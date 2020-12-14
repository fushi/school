/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 6
 * Due Date: Feb 23, 2010
 * Date Submitted: Feb 23, 2010
 */

package lab6;

public class Main {

    public static void main(String[] args) {

        if (args.length != 1){
            System.err.println("Please provide exactly 1 argument");
            System.exit(0);
        }

        student[] students = file_io.readFile(args[0]);

        int[] high = stats.high(students);
        int[] low = stats.low(students);
        double[] avg = stats.avg(students);

        file_io.writeFile(students, high, low, avg);
    }
}

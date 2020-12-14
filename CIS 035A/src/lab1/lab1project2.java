/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 1, Project 2
 * Due Date: Jan 18, 2010
 * Date Submitted: Jan 14, 2010
 */

package lab1;

public class lab1project2 {
    public static void main(String[] args) {
        int cent_input = corejava.Console.readInt("Enter a Centigrade temperature: ");
        double fahr_output = 32 + cent_input * 9/5;
        corejava.Format.printf("%.1f Fahrenheit\n", fahr_output);

        int fahr_input = corejava.Console.readInt("Enter a Fahrenheit temperature: ");
        double cent_output =  (fahr_input - 32) * 5/9;
        corejava.Format.printf("%.1f Centigrade\n", cent_output);
    }
}
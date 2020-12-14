/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 2
 * Due Date: Jan 25, 2010
 * Date Submitted: Jan 20, 2010
 */

package lab2;

public class lab2 {
    public static void main(String[] args) {

        //Collect User Input
        String description = corejava.Console.readLine("Enter a description: ");
        int year = corejava.Console.readInt("Enter year of purchase: ");
        double value = corejava.Console.readDouble("Enter purchase price: ");
        int life_span = corejava.Console.readInt("Enter life span: ");
        int method = 0;
        double total_dep = 0;
        double current_dep = value / life_span;

        while (method > 2 || method < 1)
            method = corejava.Console.readInt
                    ("Enter method of depreciation (1 for Straight Line, 2 for Double Declining): ");

        //Print item info
        System.out.printf("\nDescription: %s\n", description);
        System.out.printf("Year of purchase: %d\n", year);
        System.out.printf("Purchase price: %.2f\n", value);
        System.out.printf("Estimated Life: %d\n", life_span);

        if (method == 1) System.out.print("Method of depreciation: Straight Line\n");
        else System.out.print("Method of depreciation: Double Declining\n");

        //Print Deprication Banner
        System.out.printf("%4s%10s%12s%14s\n", "Year", "Value", "Dep. Amt", "Total Dep.");

        //Depreciation Calculation Ahead!
        while(life_span > 0){
            if (method == 2 && life_span == 1) current_dep = value;
            else if(method == 2) current_dep = value * .4;
            total_dep += current_dep;

            System.out.printf("%4d%10.2f%12.2f%14.2f\n", year, value, current_dep, total_dep);
            
            value -= current_dep;
            life_span--;
            year++;
        }
    }
}
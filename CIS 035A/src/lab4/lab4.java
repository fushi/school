/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 4
 * Due Date: Feb 11, 2010
 * Date Submitted: Feb 8, 2010
 */

package lab4;

/**
 * Lab 4 for CIS 035A, Section 63Z
 * @author John Towler
 * @version 1.0
 */

public class lab4 {
    public static void main(String[] args) {
        SavingsAccount[] saver = new SavingsAccount[2];

        //Part 1
        System.out.println("Part 1\n");
        saver[0] = new SavingsAccount(2000, "Saver1");
        saver[1] = new SavingsAccount(3000, "Saver2");

        SavingsAccount.modifyInterestRate(4);
        for(SavingsAccount element : saver){
            element.calculateMonthlyInterest();
            System.out.printf("%s balance after first month: %.2f\n", element.getName(), element.getBalance());
        }

        SavingsAccount.modifyInterestRate(5);
        for(SavingsAccount element : saver){
            element.calculateMonthlyInterest();
            System.out.printf("%s balance after second month: %.2f\n", element.getName(), element.getBalance());
        }

        //Part 2
        System.out.println("\n\nPart 2\n");
        saver[0] = new SpecialSavings(2000, "Saver1");
        saver[1] = new SpecialSavings(3000, "Saver2");
        
        java.util.Random generator = new java.util.Random();
        for(int i = 1; i <=3; i++){
            for(SavingsAccount element : saver){
                element.deposit(generator.nextDouble() * 10000);
                element.withdraw(generator.nextDouble() * 10000);
            }

            for(SavingsAccount element : saver){
                element.calculateMonthlyInterest();
                System.out.printf("%s balance after interest: %.2f\n", element.getName(), element.getBalance());
            }
            System.out.print("\n\n");
        }
    
    }
}


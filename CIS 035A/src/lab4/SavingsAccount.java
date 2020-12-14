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
public class SavingsAccount{

    //Constructors
    /**
     * Constructs a savings account with a balance of 0.
     */
    public SavingsAccount(){
        savingsBalance = 0;
    }

    /**
     * Constructs a savings account with a specified name and balance.
     * @param b Initial balance.
     * @param n Account name.
     */
    public SavingsAccount(double b, String n){
        savingsBalance = b;
    }

    //Methods
    /**
     * Sets Interest Rate.
     * @param r New Annual Interest Rate.
     */
    public static void modifyInterestRate(double r){
        annualInterestRate = r;
    }
    /**
     * @param d Amount to depost.
     */
    public void deposit(double d){
        System.out.printf("Depositing %.2f into %s\n", d, accountName);
        savingsBalance += d;
        System.out.printf("%s balance is now: %.2f\n", accountName, savingsBalance);
    }
    /**
     * @param w Amount to withdraw.
     */
    public void withdraw(double w){

        if (savingsBalance > w){
            System.out.printf("Withdrawing %.2f from %s\n", w, accountName);
            savingsBalance -= w;
        }
        else{
            System.out.printf("Withdrawing %.2f from %s\n", savingsBalance, accountName);
            savingsBalance = 0;
        }
        System.out.printf("%s balance is now: %.2f\n", accountName, savingsBalance);
    }
    /**
     * @return Account Balance.
     */
    public double getBalance(){
        return savingsBalance;
    }
    /**
     * @return Name of Account.
     */
    public String getName(){
        return accountName;
    }
    /**
     * Calculates monthly interest.
     */
    public void calculateMonthlyInterest(){
        double interest = annualInterestRate * savingsBalance / 12 / 100;
        savingsBalance += interest;
    }

    //Fields
    static double annualInterestRate;
    double savingsBalance;
    String accountName;
}

class SpecialSavings extends SavingsAccount{

    public SpecialSavings(float v, String n){
        super(v, n);
    }

    @Override
    public void calculateMonthlyInterest(){
        if (savingsBalance < 10000) savingsBalance += savingsBalance * annualInterestRate / 12 / 100;
        else savingsBalance += savingsBalance * 10 / 12 / 100;
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package finalpkg;

/**
 *
 * @author John
 */
public class Main {

    public static void main(String[] arguments) {
        CustomerManager myCustomer = new CustomerManager();
        myCustomer.cancelAllOrders().talkToManager();
    }

}

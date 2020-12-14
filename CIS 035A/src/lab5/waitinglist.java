/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 5
 * Due Date: Mar 19, 2010
 * Date Submitted: Mar 19, 2010
 */

package lab5;

import java.util.*;

public class waitinglist {

    /**
     * Constructs a waiting list object.
     */

    public waitinglist(){

    }

    /**
     * Adds a passenger to the end of the waiting list.
     * @param pass Passenger to add.
     */

    public void addPassenger(passenger pass){
        waitlist.add(pass);
    }

    /**
     * Removes a passenger from the waiting list.
     * Menu driven.
     */

    public void removePassenger(){
        this.printList();

        if(waitlist.size() == 0){
            System.out.println("There is nobody on the waitlist.");
            return;
        }

        while(true){
            int i = io.readInt("Passenger to remove: ");
            try{
                System.out.println(waitlist.remove(i-1).getName() + " successfully removed from the waitlist.");
                return;
            }
            catch(IndexOutOfBoundsException e){
                System.out.println("Not a valid number. Please try again.");
            }
        }     
    }

    /**
     * Removes the passenger at the top of the list, and returns that passenger.
     * If the waitlist is empty, it returns null.
     * @return passenger object, or null.
     */

    public passenger unwaitlistPassenger(){
        if (waitlist.size() > 0){
            return waitlist.remove(0);
        }
        else return null;
    }

    /**
     * Displays current waiting list.
     */

    public void printList(){
        int i = 1;
        System.out.println("Waiting List:");
        for (passenger pass : waitlist){
            System.out.println(i + ": " + pass.getName());
            i ++;
        }
    }

    private ArrayList<passenger> waitlist = new ArrayList<passenger>();
}

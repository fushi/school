/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 5
 * Due Date: Mar 19, 2010
 * Date Submitted: Mar 19, 2010
 */

package lab5;

public class flight {

    /**
     * Creates a flight object with a seating chart.
     * @param rows Number of rows that this flight has.
     * @param seats Number of seats per row.
     */

    public flight(int rows, int seats){
        seating = new seatingchart(rows,seats);
    }

    /**
     * Drives a menu from which you can add a passenger,
     * remove a passenger, or exit to a higher menu.
     */
    
    public void menu(){
            while(true){
                System.out.println("Please make a selection:");
                System.out.println("1: Add a passenger to this flight.");
                System.out.println("2: Remove a passenger from this flight.");
                System.out.println("3: Return to the 'Flights' menu.");
            
                switch (io.readInt("Make your selection: ")){
                    case 1:
                        this.addPassenger();
                        break;
                    case 2:
                        this.removePassenger();
                        break;
                    case 3:
                        return;
                }
            }
    }

    /**
     * Adds a passenger to the current flight.
     */

    public void addPassenger(){
        seating.addPassenger();
    }

     /**
     * Removes a passenger from the current flight.
     */

    public void removePassenger(){
        seating.removePassenger();
    }

    private seatingchart seating;
}

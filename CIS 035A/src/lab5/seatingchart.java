/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 5
 * Due Date: Mar 19, 2010
 * Date Submitted: Mar 19, 2010
 */

package lab5;

/**
 *
 * @author John
 */
public class seatingchart {

     /**
     * Creates a seating chart object with an attached waiting list.
     * @param rows Number of rows that this flight has.
     * @param seats Number of seats per row.
     */

    public seatingchart(int rows, int seats){
        chart = new passenger[rows][seats];
    }

    /**
     * Displays the current seating chart.
     */

    public void printChart(){

        int rownum = 0;

        System.out.printf("%8s", "");
        for(int i = 1; i <= chart[0].length; i++){
                System.out.printf("%-20s","Seat " + i);
        }
        System.out.println();
        for (passenger[] row : chart){
            rownum++;
            
            System.out.printf("%4s%-4d", "Row ", rownum);
            for (passenger pass : row){
                if(pass == null) System.out.printf("%-20s","Empty");
                else System.out.printf("%-20s", pass.getName());
            }
            System.out.println();
        }
    }

    /**
     * Displays current waiting list.
     */

    public void printWaitlist(){
        waitlist.printList();
    }

    /**
     * Removes a passenger from the seating chart. Menu driven.
     */

    public void removePassenger(){       
        while(true){
            int selection = io.readInt("Enter 1 for the seating chart, 2 for the waitlist: ");

            if ( selection == 2){
                waitlist.removePassenger();
                return;
            }
            if (selection == 1){
                this.printChart();

                System.out.println("Choose a seat to vacate: ");

                while(true){
                    int row = io.readInt("Row: ");
                    int seat = io.readInt("Seat: ");

                    try{
                        chart[row-1][seat-1] = waitlist.unwaitlistPassenger();
                        if (chart[row-1][seat-1] == null) System.out.println("Row " + (row) + " seat " + (seat) + " is now empty." );
                        else System.out.println("Row " + (row) + " seat " + (seat) + " is now assigned to " + chart[row-1][seat-1].getName() );
                        return;
                    }
                    catch(ArrayIndexOutOfBoundsException e){
                        System.out.println("Row " + (row) + " seat " + (seat) + " is not a valid position. Please Try again.");
                    }
                }
            }
        }
    }

    /**
     * Adds a passenger to the seating chart. If the seating chart is full,
     * the passenger is automatically added to the waitlist
     */

    public void addPassenger(){

        passenger pass = new passenger();

        if(this.isFull()){
            System.out.println("Seating chart is full, waitlisting " + pass.getName() + ".");
            waitlist.addPassenger(pass);
            return;
        }

        this.printChart();
        System.out.println("Please Choose an Empty Seat");

        while(true){
            int row = io.readInt("Row: ");
            int seat = io.readInt("Seat: ");

            try{
                if(chart[row - 1][seat - 1] != null) System.out.println("That seat is not empty.");
                else{
                    chart[row - 1][seat - 1] = pass;
                    System.out.println(chart[row - 1][seat - 1].getName() + " is assigned to row " + (row) + " seat " + (seat) + "." );
                    return;
                }
            }
            catch(ArrayIndexOutOfBoundsException e){
                System.out.println("Row " + (row) + " seat " + (seat) + " is not a valid position. Please Try again.");
            }
        }
    }

    /**
     * Determines if the seating chart is full.
     * @return True for full, false for empty.
     */

    public boolean isFull(){
        for (passenger [] element1 : chart){
            for(passenger element2 : element1){
                if (element2 == null) return false;
            }
        }
        return true;
    }

    /**
     * Inspects a given seat, to determine what passenger,
     * if any, is in the seat. Menu Driven.
     */

    public void getPassenger(){

        this.printChart();
        System.out.println("Choose a seat to inspect: ");

        while(true){

            int row = io.readInt("Row: ");
            int seat = io.readInt("Seat: ");

            try{
                System.out.println(chart[row-1][seat-1].getName() + " is sitting in row " + (row) + " seat " + (seat) + "." );
                return;
            }
            catch(ArrayIndexOutOfBoundsException e){
                System.out.println("Row " + (row) + " seat " + (seat) + " is not a valid position. Please Try again.");
            }
            catch(NullPointerException e){
                System.out.println("Row " + (row) + " seat " + (seat) + " is unoccupied." );
                return;
            }
        }
    }

    private passenger [][] chart;
    private waitinglist waitlist = new waitinglist();
}

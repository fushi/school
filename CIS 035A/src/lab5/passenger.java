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
public class passenger {

     /**
     * Creates a passenger object.
     * User is prompted for First and Last name.
     */

    public passenger(){
        String correct;

        do{
        fname = io.readString("Enter the passengers First Name: ");
        lname = io.readString("Enter the passengers Last Name: ");

        do{
            correct = io.readString(fname + " " + lname + ": is this correct? (y/n): ");
        }while(!(correct.contentEquals("y") || correct.contentEquals("n")));

        }while(correct.contentEquals("n"));
    }
    
    /**
    * Creates a passenger object.
    * @param first First name of passenger.
    * @param last Last name of passenger.
    */
    
    public passenger(String first, String last){
        fname = first;
        lname = last;
    }

    public void setFName(String first){
        fname = first;
    }

    public void setLName(String last){
        lname = last;
    }

    public String getName(){
        return lname + ", " + fname;
    }



    private String lname;
    private String fname;
}

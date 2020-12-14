/*
 * DBTest.java
 *
 * Created on December 18, 2005, 9:39 AM
 *
 * Create this file under 'session2' package.
 */

package session2;

/**
 *
 * @author Rolly
 *
 * Follow instructions given in session1 to compile and run this program.
 */
public class DBTest {
    
    public static void main(String[] args) {
	   DBProc dbp = new DBProc();
	   dbp.insertEmployee(512, "Ball", "Pen", 215.35, "2005-07-03", "X21");
	   
	   dbp.insertDepartment("D64", "Animation");
	   dbp.displayAllEmpsByDept();
	   System.out.println(dbp.getSalary(122));
	   dbp.deleteEmployee(512);
	   
	}
}

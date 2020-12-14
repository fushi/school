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
	   dbp.insertEmployee(22, "King", "Kong", 215.35, "2005-07-03", "X21");
	   dbp.insertEmployee(23, "Jimmy", "Neutron", 161.35, "2002-01-08", "M25");
	   dbp.deleteEmployee(6);
	   dbp.insertDepartment("D32", "Animation");
	   dbp.displayAllEmpsByDept();
	}
}

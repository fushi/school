/*
 * DBTrans.java
 *
 * Created on December 17, 2005, 6:49 PM
 *
 * Here's how I run this class manually (of course, mysql must be running):
 * java -classpath .;<dir path>\mysql-conn.jar DBTrans
 *
 *To build the project in Netbeans:
 *  1. File -> New Project -> General -> Java Application
 *  2. Name this project as 'jdbc'. De-select the Main class field.
 *  3. In the projects window, right-click Source Packages -> Java class
 *  4. Name the class DBTrans.  Make the package name: 'session1'.
 *  5. Add mysql-conn.jar file to the project's libraries by right-clicking
 *     on the Libraries node. 
 *  6. To compile:  
 *     Right-click on DBTrans.java - Compile File
 *  7. To run:
 *     Make sure mysql is running. Right-click on DBTrans.java - Run File
 * 
 */

package session1;
import java.sql.*;
/**
 *
 * @author Rolly
 */
public class DBTrans {
    
  	private Connection dbconn;
	private Statement stmt;


	public DBTrans() {

	// This resource locator line will be used when running this
	// program in the same machine as the mysql dbserver is running.
	  String url = "jdbc:mysql://localhost/test";

	  // Line below will be used when connecting from another host.
	  // The name of the machine that has the mysql db is voyager.deanza.edu.
	  // mysql on rebekah is using port 3306 for communication.
	  //
	  //String url = "jdbc:mysql://voyager.deanza.edu:3306/test";
	
	  try {
	// Following line creates an instance of the JDBC driver.
	     Class.forName("com.mysql.jdbc.Driver").newInstance();
	
	//Establishing database connection.
	     dbconn = DriverManager.getConnection(url, "dbuser1", "welcome");

	     // User dbuser2 was granted access to connect to mysql db.
	     // Line below will be used when connecting to voyager.deanza.edu.
	     //
	     //dbconn = DriverManager.getConnection(url, "cis53", "distjava");


	//Creating a Statement object - used to submit SQL queries.
	     stmt = dbconn.createStatement();

	  }catch (ClassNotFoundException e) {
	     e.printStackTrace();
	  }catch (SQLException sqlex) {
	     sqlex.printStackTrace();
	  }catch (Exception ex) {
	     ex.printStackTrace();
	  }
	}

	public void displayTableRows() {
	    int empId = 0;
	    String empFirstName = null;
	    String empLastName = null;
	    double empSalary = 0.0;
	    // Do not confuse with java.util.Date
	    java.sql.Date empHireDate = null;
	    int age = 0;
	    String empDeptId = null;

	    String sql = "select emp_id, emp_firstname, " +
		         "emp_lastname, emp_salary, " +
			 "emp_hiredate, emp_deptid " +
			 "from employee ";
	    ResultSet rs = null; 

	     try {
	// Execute the SQL query. Results will be in ResultSet object.
	        rs = stmt.executeQuery(sql);

	// Iterate through the result set, retrieve values and display.
	  	while(rs.next()) {
		  empId = rs.getInt(1);
		  empFirstName = rs.getString(2);
		  empLastName = rs.getString(3);
		  empSalary = rs.getDouble(4);
		  empHireDate = rs.getDate(5);
		  empDeptId = rs.getString(6);

		  System.out.println(empId + "\t" + empFirstName + "\t" +
		  		empLastName + "\t" + empSalary + "\t" +
				empHireDate + "\t" + empDeptId);
		}
	     }catch (SQLException e) {
	       e.printStackTrace();
	     }catch (Exception ex) {
	        ex.printStackTrace();
	     }finally {
		  try {
		     rs.close();
		     stmt.close();
		     dbconn.close();
	           }catch (SQLException e) {
	               e.printStackTrace();
		   }
	     }

	}

	public static void main(String[] args) {
		DBTrans dbt = new DBTrans();
		dbt.displayTableRows();
	}
    
}

/*
 * DBProc.java
 *
 */

package session11;
import java.sql.*;
import java.util.*;
/**
 *
 * @author Rolly
 */
public class DBProc {
    private Connection conn;
    Statement stmt;
    /** Creates a new instance of DBProc */
    public DBProc() {
    }
    
    public DBProc(String url, String driver, String login, String password) {
	   DBConnection dbc = new DBConnection();
	   dbc.setConnectionInfo(url, driver, login, password);
	   conn = dbc.getConnection();
	   try {
	     stmt = conn.createStatement();
	   }catch (SQLException sqlex) {
	     sqlex.printStackTrace();
	  }
	 }


	public ArrayList getEmployees() {

	   ArrayList <Employee> emps = new ArrayList <Employee> ();
	   String query = "select emp_id, emp_firstname, emp_lastname, " +
		   	  "emp_salary, emp_hiredate, emp_deptid " +
		          "from employee ";
	   try {
	        ResultSet rs = stmt.executeQuery(query);
	        while (rs.next()) {
	   	  Employee emp = new Employee();
		  int empId = rs.getInt("emp_id");
		  String empFirstName = rs.getString("emp_firstname");
		  String empLastName = rs.getString("emp_lastname");
		  double empSalary = rs.getDouble("emp_salary");
		  String empHireDate = rs.getString("emp_hiredate");
		  String empDeptId = rs.getString("emp_deptid");

		  emp.setEmpId(empId);
		  emp.setEmpFirstName(empFirstName);
		  emp.setEmpLastName(empLastName);
		  emp.setEmpSalary(empSalary);
		  emp.setEmpHireDate(empHireDate);
		  emp.setEmpDeptId(empDeptId);
		  
		  emps.add(emp);
		}
	   }catch (SQLException e) {
	       e.printStackTrace();
	   }

	   return emps;
	}
}

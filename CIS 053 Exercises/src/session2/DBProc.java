/*
 * DBProc.java
 *
 * Created on December 18, 2005, 9:35 AM
 *
 * 1. Create this file under 'session2' package.
 */

package session2;
import java.sql.*;
/**
 *
 * @author Rolly
 */
public class DBProc {
	private Connection conn;
	private Statement stmt;
    
    /** Creates a new instance of DBProc */
    public DBProc() {
     	   DBConnection dbc = new DBConnection();
     	   conn = dbc.getConnection();
     	   try {
     		   stmt = conn.createStatement();
     	   }
     	   catch (SQLException sqlex) {
     		   sqlex.printStackTrace();
     	   }  
    }
   
	public void insertEmployee(int empId, String empFirstName,
				  String empLastName, double empSalary,
				  String empHireDate, String empDeptId) {
	   String query = "insert into employee values (" +
	   		  empId + " , '" + empFirstName + "', '" +
			  empLastName + "', " + empSalary + ", '" +
			  empHireDate + "', '" + empDeptId + "')";
	   try {
	        stmt.executeUpdate(query);
	   }
	   catch (SQLException e) {
		   e.printStackTrace();
	   }
	}

	public void insertDepartment(String deptId, String deptName) {
		String query = "insert into department values ('" +
		    	    deptId + "', '" + deptName + "')";
		try {
			stmt.executeUpdate(query);
		}catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public void deleteEmployee(int empId) {
	   String query = "delete from employee where emp_id = " + empId;
	   try {
	        stmt.executeUpdate(query);
	   }catch (SQLException e) {
	       e.printStackTrace();
	   }
	}

	public void displayAllEmpsByDept() {
		String query = "select emp_id, emp_firstname, emp_lastname, emp_salary, dept_name " +
		          "from employee, department " +
			  "where emp_deptid = dept_id " +
			  "order by dept_name ";
	   try {
		   ResultSet rs = stmt.executeQuery(query);
		   while (rs.next()) {
			   String empFirstName = rs.getString("emp_firstname");
			   String empLastName = rs.getString("emp_lastname");
			   String deptName = rs.getString("dept_name");

			   System.out.println(empFirstName + " " + empLastName + "\t" + deptName);
	      }
	   }
	   catch (SQLException e) {
		   e.printStackTrace();
	   }
	}
	
	//Add Service method: public double getSalary(int empId)
	
	public double getSalary(int empId){
		String query = "select emp_salary from employee where emp_id = " + empId;
		double salary = 0.0;
		
		
		
		try{
			ResultSet rs = stmt.executeQuery(query);
			rs.next();
				
				salary = rs.getDouble(1);
			
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		return salary;
	}
}

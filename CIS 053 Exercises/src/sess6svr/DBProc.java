package sess6svr;

import java.util.*;
import java.sql.*;

public class DBProc {

	private Connection conn;
	Statement stmt;

	public DBProc() {
	   DBConnection dbc = new DBConnection();
	   conn = dbc.getConnection();
	   try {
	     stmt = conn.createStatement();
	   }catch (SQLException sqlex) {
	     sqlex.printStackTrace();
	  }
	 }



	public Vector getAllEmpsByDept() {
	
	   Vector retVec = new Vector();

	   String query = "select emp_firstname, emp_lastname, dept_name " +
		          "from employee, department " +
			  "where emp_deptid = dept_id " +
			  "order by dept_name ";

	   try {
	      ResultSet rs = stmt.executeQuery(query);
	      while (rs.next()) {
		  String empFirstName = rs.getString("emp_firstname");
		  String empLastName = rs.getString("emp_lastname");
		  String deptName = rs.getString("dept_name");

		  String row = empFirstName + " " + empLastName +
				     "\t" + deptName;
		  retVec.addElement(row);
	      }
	   }catch (SQLException e) {
	       e.printStackTrace();
	   }

	   return retVec;
	}
}

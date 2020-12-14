package session4;
import java.sql.*;

public class DBProc {

	public final static char UPDATE = 'U';
	public final static char DELETE = 'D';
	public final static char INSERT = 'I';

	private Connection conn;

	public DBProc() {
	   DBConnection dbc = new DBConnection();
	   conn = dbc.getConnection();
	 }

	public Statement getStatement() {
	   Statement stmt = null;
	   try {
	     // In order to get an updatable result set, the Statement
	     // object we create must be updatable.
	     stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, 
			     		 ResultSet.CONCUR_UPDATABLE);
	   }catch (SQLException ex) {
	       ex.printStackTrace();
	   }

	   return stmt;
	}

	// The table that the following method is accessing has a
	// primary key.  The result set will not be updatable, if the
	// table has no defined primary key. The column with the primary
	// key must be included in the select statement.  In this
	// exercise, the 'employee' table has emp_id as its primary key.
	//
	public void maintainEmployeeTable(Employee e, char maintFlag) {

	   String query = "select emp_id, emp_firstname, emp_lastname, " +
		   	  "emp_salary, emp_hiredate, emp_deptid " +
		          "from employee ";

	   Statement stmt = getStatement();
	   try {
	        ResultSet rs = stmt.executeQuery(query);
		switch (maintFlag) {
		  case UPDATE: 
		    int row = 1;
	            while (rs.next()) {
		      if (rs.getInt("emp_id") == e.getEmpId()) {
			 rs.absolute(row);
			 rs.updateDouble("emp_salary", e.getEmpSalary());
			 rs.updateString("emp_hiredate", e.getEmpHireDate());
			 rs.updateString("emp_deptid", e.getEmpDeptId());
			 rs.updateRow();
		      }
		      ++row;
		    }
		    break;

		  case DELETE: 
	            while (rs.next()) {
		      if (rs.getInt("emp_id") == e.getEmpId()) {
			//The cursor is already positioned to the row
			//we want to delete.
			rs.deleteRow();
		      }
		    }
		    break;

		  case INSERT:
		      rs.moveToInsertRow();
		      rs.updateInt("emp_id", e.getEmpId());
		      rs.updateString("emp_firstname", e.getEmpFirstName());
		      rs.updateString("emp_lastname", e.getEmpLastName());
		      rs.updateDouble("emp_salary", e.getEmpSalary());
		      rs.updateString("emp_hiredate", e.getEmpHireDate());
		      rs.updateString("emp_deptid", e.getEmpDeptId());
		      rs.insertRow();
		    break;
		}

		// Explicit closure of ResultSet object, instead of
		// waiting for automatic closure.
		rs.close();

	   }catch (SQLException ex) {
	       ex.printStackTrace();
	   }

	   // Explicit closure of Statement object, instead of
	   // waiting for automatic closure.
	   try {
	       stmt.close();
	   }catch (SQLException ex) {
	       ex.printStackTrace();
	   }

	}


}

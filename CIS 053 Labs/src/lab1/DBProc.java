package lab1;
import java.sql.*;
import java.util.*;

/**
 * Class to interact with a database.
 * 
 * Some code borrowed from CIS 053 Exercises.
 * @author John Towler
 * @version 1.0: Oct 10, 2011
 */
public class DBProc {

	private DBConnection dbc;

	/**
	 * Connects to the DB, grabs the data from the employee table, and
	 * packages the table data in a vector of vectors.
	 * @param propFilePath String containing the path to the properties file that contains
	 * the DB connection information.
	 */
	public DBProc(String propsFilePath) {
		dbc = new DBConnection(propsFilePath);
	}

	/**
	 * Connects to the DB, grabs the data from the employee table, and
	 * packages the table data in a vector of vectors.
	 * @return A vector of vectors representing the employee table.
	 */
	public Vector<Vector<?>> getEmployees() {
		Vector<Vector<?>> resultVector = new Vector<Vector<?>>();
		String query = "select emp_id, emp_firstname, emp_lastname, emp_salary, " 
			+ "emp_hiredate, emp_deptid from employee order by emp_id";
		try {
			Connection conn = dbc.getConnection();
			PreparedStatement prepStmt = conn.prepareStatement(query);
			ResultSet rs = prepStmt.executeQuery();
			
			while (rs.next()) {
				Vector<String> tempVector = new Vector<String>();
				
				tempVector.add(rs.getString("emp_id"));
				tempVector.add(rs.getString("emp_firstname"));
				tempVector.add(rs.getString("emp_lastname"));
				tempVector.add(rs.getString("emp_salary"));
				tempVector.add(rs.getString("emp_hiredate"));
				tempVector.add(rs.getString("emp_deptid"));
				
				resultVector.add(tempVector);
			}
			dbc.closeConnection();
		}
		catch (SQLException e) {
			e.printStackTrace();
		}
		
		return resultVector;
	}
	
	
	/**
	 * Connects to the DB, grabs the data from the departments table, and
	 * packages the table data in a vector of vectors.
	 * @return A vector of vectors representing the departments table.
	 */
	public Vector<Vector<?>> getDepartments() {

		Vector<Vector<?>> resultVector = new Vector<Vector<?>>();

		String query = "select dept_id, dept_name from department order by dept_id";
		try {

			Connection conn = dbc.getConnection();
			PreparedStatement prepStmt = conn.prepareStatement(query);
			ResultSet rs = prepStmt.executeQuery();
			

			while (rs.next()) {
				Vector<String> tempVector = new Vector<String>();

				tempVector.add(rs.getString("dept_id"));
				tempVector.add(rs.getString("dept_name"));

				resultVector.add(tempVector);
			}
			dbc.closeConnection();
		}
		catch (SQLException e) {
			e.printStackTrace();
		}

		return resultVector;
	}

}

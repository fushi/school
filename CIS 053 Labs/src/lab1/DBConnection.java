/**
 * John Towler
 * CIS 053
 * Lab 1
 * Due Date: October 12, 2011
 * Date Submitted: October 12, 2011
 */

package lab1;

import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

/**
 * Class to connect to a database, with the connection information coming from
 * a properties file.
 * 
 * Some code borrowed from CIS 053 Exercises.
 * @author John Towler
 * @version 1.0: Oct 10, 2011
 */

public class DBConnection {

	private Connection conn;
	private String url;
	private String driver;
	private String login;
	private String password;

	/**
	 * Constructor that gets the DB connection information from a properties file. 
	 * @param propFilePath String containing the path to the properties file that contains
	 * the DB connection information.
	 */
	public DBConnection(String propFilePath) {
		getConnectionInfo(propFilePath);
	}
	
	/**
	 * Opens a properties file, and puts the information into private instance variables. 
	 * @param propFilePath String containing the path to the properties file that contains
	 * the DB connection information.
	 */
	private void getConnectionInfo(String propFilePath) {
		Properties props = new Properties();
		try {
			FileInputStream propsData = new FileInputStream(propFilePath);
			props.load(propsData);
			propsData.close();
		}

		catch (IOException e) {
			e.printStackTrace();
			return;
		}

		url = props.getProperty("url");
		driver = props.getProperty("driver");
		login = props.getProperty("login");
		password = props.getProperty("password");
	}

	
	/**
	 * Obtains a connection to the DB.
	 * @return A connection object reference.
	 */
	public Connection getConnection() throws SQLException {

		// If there's no connection yet, there's no driver: Get one!
		try {
			if(conn == null){
				Class.forName(driver).newInstance();
			}
		}
		catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		catch (Exception ex) {
			ex.printStackTrace();
		}
		conn = DriverManager.getConnection(url, login, password);
		return conn;
	}
	
	/**
	 * Closes the connection to the DB.
	 * NOTE: This does not free the connection object.
	 * @return A connection object reference.
	 */
	public void closeConnection() throws SQLException {
			conn.close();	
	}
}

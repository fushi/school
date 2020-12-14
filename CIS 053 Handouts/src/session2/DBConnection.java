/*
 * DBConnection.java
 *
 * Created on December 17, 2005, 7:14 PM
 *
 * 1. Create this class in the SAME project as session1. Only create a
 *    different package, 'session2', for it. 
 * 2. Copy the dbconnection.props file in the same 'session2' package folder.
 *    (In netbeans, you can find the actual, physical folder by clicking on
 *     the Files tab.)
 * 3. The files: DBProc.java & DBTest.java should also be created in the
 *    'session2' package.
 */

package session2;
import java.sql.*;
import java.util.*;
import java.io.*;
/**
 *
 * @author Rolly
 */
public class DBConnection {
	private Connection conn;
	private Statement stmt;
	private String url;
	private String driver;
	private String login;
	private String password;
    /** Creates a new instance of DBConnection */
    public DBConnection() {
        	conn = null;
		stmt = null;
		getConnectionInfo();
    }
    
	private void getConnectionInfo() {
		Properties props = new Properties();
		try {
		   FileInputStream propsData = 
			new FileInputStream("C:\\Documents and Settings\\Rolly\\java\\cis53\\jdbc" +
                           "\\src\\session2\\dbconnection.props");	
                   props.load(propsData);
		   propsData.close();
		} catch (IOException e) {
		  e.printStackTrace();
		  return;
		}
		
		url = props.getProperty("url");
		driver = props.getProperty("driver");
		login = props.getProperty("login");
		password = props.getProperty("password");
	}

	public Connection getConnection() {

		try {
		     Class.forName(driver).newInstance();
	             conn = DriverManager.getConnection(url, login, password);
		}catch (ClassNotFoundException e) {
	           e.printStackTrace();
	  	}catch (SQLException sqlex) {
	           sqlex.printStackTrace();
	  	}catch (Exception ex) {
	           ex.printStackTrace();
	  	}

		return conn;
	}

}

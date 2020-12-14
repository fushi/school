/*
 * DBConnection.java
 *
 */

package session11;
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
    }
    
    public void setConnectionInfo(String url, String driver,
				       String login, String password) {
		
		this.url = url;
		this.driver = driver;
		this.login = login;
		this.password = password;
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

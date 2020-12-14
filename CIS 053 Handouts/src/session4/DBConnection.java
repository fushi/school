package session4;
import java.sql.*;
import java.util.*;
import java.io.*;

public class DBConnection {
	private Connection conn;
	private Statement stmt;
	private String url;
	private String driver;
	private String login;
	private String password;

	public DBConnection() {
		conn = null;
		stmt = null;
		getConnectionInfo();
	}

	private void getConnectionInfo() {
		Properties props = new Properties();
		try {
		   FileInputStream propsData = 
			new FileInputStream("C:\\Documents and Settings\\Rolly\\java\\cis53\\" +
                           "jdbc\\src\\session4\\dbconnection.props");
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

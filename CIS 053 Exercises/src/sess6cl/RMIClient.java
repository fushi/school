package sess6cl;
/*
 Do the usual javac compile of the client classes.
 Remember that the ConnectionInfo class uses the connection.props file
 Do not forget to make the stub class available to this client.
 To run this client:
 1. java  sess6cl.RMIClient
 */
import sess6svr.*;
import java.util.*;
import java.rmi.*;
import java.rmi.registry.*;

public class RMIClient {

	public static void main(String[] args){

	try{

	   Registry reg = null;

	   Properties props = ConnectionInfo.getConnectionInfo();
	   int port = Integer.parseInt(props.getProperty("port"));
	   String regURL = props.getProperty("reg_url");
	   String hostname = props.getProperty("hostname");

	   reg = LocateRegistry.getRegistry(hostname, port);

	   if (reg != null) {
	      RMIServerIntf rs = (RMIServerIntf)reg.lookup(regURL);

	      Vector rows = rs.getAllEmps();
	      for (int idx = 0; idx < rows.size(); ++ idx) {
		      System.out.println((String)rows.elementAt(idx));
	      }
	   }
	   else
	     System.out.println("Unable to locate registry");
	}catch (Exception e) {
	  e.printStackTrace();
	}

	}
}


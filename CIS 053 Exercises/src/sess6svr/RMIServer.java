package sess6svr;
/*
 Compile the server-side classes. Use rmic to generate the stub class.
 Ex. rmic sess6svr.RMIServer
 Copy the generated stub class to the client's classes directory.
 To run this server:
 1. Make sure your DB server is up and running.
    Copy mysql-conn.jar to your server's classes directory.
 2. java  -classpath .;<path of your jdbc driver> 
	-Djava.rmi.server.hostname=<your hostname>
 	-Djava.rmi.server.codebase=<your server codebase> RMIServer
 3. Here's how I do it:
 java  -classpath .;.\sess6svr\mysql-conn.jar -Djava.rmi.server.hostname=rebekah 
 -Djava.rmi.server.codebase=file:c:\docume~1\rolly\java\cis53\rmi\build\classes/ sess6svr.RMIServer
*/

import java.util.*;
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

public class RMIServer extends UnicastRemoteObject
			   implements RMIServerIntf{

	DBProc dbProc = null;

	public RMIServer() throws RemoteException{
		super();
		dbProc = new DBProc();
	}

	public Vector getAllEmps() throws RemoteException{
		return dbProc.getAllEmpsByDept();
	}


	public static void main(String[] args) {

		try {
		  Properties props = ConnectionInfo.getConnectionInfo();
		  int port = Integer.parseInt(props.getProperty("port"));
		  String regURL = props.getProperty("reg_url");
		  RMIServer rs = new RMIServer();
		  //Instead of rmiregistry, create own registry object.
		  Registry r = LocateRegistry.createRegistry(port);
		  r.rebind(regURL, rs);
		  System.out.println("RMI Server is ready.");
		}catch (Exception e) {
		  e.printStackTrace();
		}
	}
}


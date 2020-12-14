package sess5svr;
/*
 Write this server class in a separate directory from the client class.
 1. Compile all server-side classes.
 2. After a successful compilation, do not forget to run rmic manually:
    (If you wrote code using netbeans, cd to: <proj path>\rmi\build\classes folder.)
 	rmic  sess5svr.RMIServer
    This will produce the RMIServer_Stub.class file.

Here's how you'll run this server:
 3. Run rmiregistry in a separate command prompt window:  start rmiregistry
 4. java -Drmi.server.hostname=localhost -Djava.rmi.server.codebase=file:<codebase path>/ sess5svr.RMIServer
 
 java -Drmi.server.hostname=localhost -Djava.rmi.server.codebase=file:/javashortcut/ sess5svr.RMIServer
 
 Here's an example when I run on my machine:
 
 java -Drmi.server.hostname=localhost 
 -Djava.rmi.server.codebase=file:c:\docume~1\rolly\java\cis53\rmi\build\classes/ sess5svr.RMIServer
*/

import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

// Make this RMI server a subclass of UnicastRemoteObject
// In addition, this class implements an interface RMIServerIntf
// of the type Remote.
public class RMIServer extends UnicastRemoteObject
			   implements RMIServerIntf{

	public RMIServer() throws RemoteException{
		super();
	}
	public String sayHello() throws RemoteException{
		System.out.println("RMIServer: sayHello()");
		return ("Hello");
	}

	public String sayHelloAgain() throws RemoteException{
		System.out.println("RMIServer: sayHelloAgain()");
		return ("Hello Again");
	}

	public static void main(String[] args) {

		try {

		  RMIServer rs = new RMIServer();
		  // This server is bound(registered) to the RMI
		  // registry object running on the host rebekah.
		  // This server's locator name is: RMIServer
		  Naming.rebind("//localhost/RMIServer", rs);
		  System.out.println("RMI Server is bound.");
		}catch (Exception e) {
		  e.printStackTrace();
		}
	}
}


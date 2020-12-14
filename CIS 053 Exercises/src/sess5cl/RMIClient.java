/*
Write this client class in a separate package('sess5cl') from the server class.
 1. Notice how this class is importing the RMIServerIntf class.
 2. Compile this class.
 3. You'll also need to copy RMIServerImpl_Stub.class file from the server
    classes directory to this client's classes directory in order to run it. 
    (See instructions in RMIServer class on how to run rmic to generate 
    the stub class.)

 Run this program, manually, in a separate command prompt window:
	java sess5cl.RMIClient
 */
package sess5cl;

import sess5svr.*;
import java.rmi.*;
import java.rmi.registry.*;

public class RMIClient {

	public static void main(String[] args){

		try{
			RMIServerIntf rs = (RMIServerIntf)Naming.lookup("//localhost/RMIServer");
			// The stub class is used by RMI to invoke the two
			// remote methods below.
			System.out.println(rs.sayHello());
			System.out.println(rs.sayHelloAgain());
		}catch (Exception e) {
			e.printStackTrace();
		}

	}
}


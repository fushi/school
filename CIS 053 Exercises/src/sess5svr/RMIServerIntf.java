package sess5svr;
import java.rmi.*;

public interface RMIServerIntf extends Remote{

	public String sayHello() throws RemoteException;
	public String sayHelloAgain() throws RemoteException;
}

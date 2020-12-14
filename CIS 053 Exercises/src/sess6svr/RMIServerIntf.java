package sess6svr;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;

public interface RMIServerIntf extends Remote{

	public Vector getAllEmps() throws RemoteException;
}

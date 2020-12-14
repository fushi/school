package sess6svr;
import java.util.*;
import java.io.*;

public class ConnectionInfo {

	public static Properties getConnectionInfo() {
		Properties props = new Properties();
		try {
		   FileInputStream propsData = 
			new FileInputStream("C:\\Documents and Settings\\Rolly\\java\\cis53\\rmi\\" +
                           "src\\sess6svr\\connection.props");
		   props.load(propsData);
		   propsData.close();
		} catch (IOException e) {
		  e.printStackTrace();
		}
		return props;
	}
}

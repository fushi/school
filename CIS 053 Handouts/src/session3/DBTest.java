package session3;
public class DBTest {
	public static void main(String[] args) {
	   DBProc dbp = new DBProc();
	   dbp.insertDepartment("G422", "Tailoring");
	   Employee e = dbp.getEmployee(20);
	   System.out.println(e);
	   e = dbp.getEmployee(1);
	   System.out.println(e);
	   Department d = dbp.getDepartment("B33");
	   System.out.println(d);
	   d = dbp.getDepartment("G4");
	   System.out.println(d);
           dbp.closeConnection();
	}
}

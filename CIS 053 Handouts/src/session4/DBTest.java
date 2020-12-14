package session4;
public class DBTest {
	public static void main(String[] args) {

	   DBProc dbp = new DBProc();

	   Employee e = new Employee();
	   e.setEmpId(4);
	   e.setEmpFirstName("Wonder");
	   e.setEmpLastName("Girl");
	   e.setEmpSalary(2372.22);
	   e.setEmpHireDate("2002-07-18");
	   e.setEmpDeptId("M25");
	   dbp.maintainEmployeeTable(e, DBProc.UPDATE);
	   
	   Employee e2 = new Employee();
	   e.setEmpId(23);
	   e.setEmpFirstName("Capt");
	   e.setEmpLastName("America");
	   e.setEmpSalary(521.00);
	   e.setEmpHireDate("2004-06-08");
	   e.setEmpDeptId("M25");
	   dbp.maintainEmployeeTable(e, DBProc.INSERT);
	   
	   Employee e3 = new Employee();
	   e.setEmpId(100);
	   e.setEmpFirstName("Uncle");
	   e.setEmpLastName("Sam");
	   e.setEmpSalary(234.57);
	   e.setEmpHireDate("2005-12-08");
	   e.setEmpDeptId("DEP");
	   dbp.maintainEmployeeTable(e, DBProc.DELETE);
	}
}

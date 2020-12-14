package session3;

public class Department {
	private String deptId;
	private String deptName;

	public Department() {
	   deptId = null;
	   deptName = null;
	}

	public void setDeptId(String id) {
	   deptId = id;
	}

	public void setDeptName(String name) {
	   deptName = name;
	}

	public String getDeptId() {
	   return deptId;
	}

	public String getDeptName() {
	   return deptName;
	}

	public String toString() {
	   String retVal;
	   retVal = "DeptId: " + deptId + "\n" + "DeptName: " + deptName;
	   return retVal;
	}
}

/*
 * Make this a singleton class.
 * Also, overload the constructor with one that takes a parameter
 * for each of the instance variables.
 * Write a tester class to make sure you now have a singleton class.
 */
package excs4;
final public class Employee {

       private int empId;
       private String empFirstName;
       private String empLastName;
       private double empSalary;
       private String empHireDate;
       private String empDeptId;
       private static Employee instance = null;

       private Employee() {
          empId = -1;
          empFirstName = null;
          empLastName = null;
          empSalary = 0.0;
          empHireDate = null;
          empDeptId = null;
       }
       
       private Employee(int eId, String eFN, String eLN, double eSal, String eHD, String eDI){
    	   empId = eId;
    	   empFirstName = eFN;
    	   empLastName = eLN;
    	   empSalary = eSal;
    	   empHireDate = eHD;
    	   empDeptId = eDI;   	   
       }

       public static Employee getInstance(){
    	   if (instance == null)
    		   instance = new Employee();
    	   return instance;
       }

       public int getEmpId() {
          return empId;
       }

       public String getEmpFirstName() {
          return empFirstName;
       }

       public String getEmpLastName() {
          return empLastName;
       }

       public double getEmpSalary() {
          return empSalary;
       }

       public String getEmpHireDate() {
          return empHireDate;
       }

       public String getEmpDeptId() {
          return empDeptId;
       }

       public String toString() {
          String retVal = "Empid: " + empId + "\n" +
                          "EmpFirstName: " + empFirstName + "\n" +
                          "EmpLastName: " + empLastName + "\n" +
                          "EmpSalary: " + empSalary + "\n" +
                          "EmpHireDate: " + empHireDate + "\n" +
                          "EmpDeptId: " + empDeptId + "\n";
          return retVal;
       }

       public static void main(String [] args){
    	   Employee foo = Employee.getInstance();
    	   Employee bar = Employee.getInstance();
    	   
    	   if (foo == bar)
    		   System.out.println("It works!");
    	   else System.out.println("It failed!");
       }
}


package session7;
//Session 7
//
import java.lang.reflect.*;
import java.util.*;

public class ClassManipulator {

	public Object createObject(String className) {
      	   Object object = null;
      	   try {
             Class classDefinition = Class.forName(className);
	     //The class being instantiated MUST have a no-argument constructor
             object = classDefinition.newInstance();
      	   } catch (InstantiationException e) {
             e.printStackTrace();
      	   } catch (IllegalAccessException e) {
             e.printStackTrace();
      	   } catch (ClassNotFoundException e) {
             e.printStackTrace();
      	   }

      	   return object;
    	}

	public Object createObject(String className, Class[] argTypes,
				   Object[] argVals) {
	   Object object = null;

	   try {
             Class classDefinition = Class.forName(className);
	     // Here, the constructor being used is NOT the no-argument constructor
	     Constructor cons = classDefinition.getConstructor(argTypes);
	     object = cons.newInstance(argVals);
	   } catch (ClassNotFoundException e) {
             	   e.printStackTrace();
      	   } catch (NoSuchMethodException e) {
             	   e.printStackTrace();
      	   } catch (InstantiationException e) {
             	   e.printStackTrace();
	   } catch (IllegalAccessException e) {
             	   e.printStackTrace();
	   } catch (InvocationTargetException e) {
             	   e.printStackTrace();
           }
	   
	   return object;
	}

	public Object getFieldValue(Object obj, String fieldName) {

	     Object object = null;
	     Class c = obj.getClass(); //Create a Class object

	     try {
		 Field fld = c.getField(fieldName); //Create a Field object using the
						    //field name
		 object = fld.get(obj); // The field value is in the form of an object.
					// Primitive values are returned in their
					// corresponding wrapper class.
	     }catch (NoSuchFieldException e) {
             	   e.printStackTrace();
      	     } catch (SecurityException e) {
             	   e.printStackTrace();
      	     } catch (IllegalAccessException e) {
             	   e.printStackTrace();
     	     }  
	   
	     return object;
	}

	public void setFieldValue(Object obj, String fieldName, Object fieldValue) {

	     
	     Class c = obj.getClass();  //Create a Class object

             try {  
                 Field fld = c.getField(fieldName); //Create a Field object using the
						    //field name
                 fld.set(obj, fieldValue);       //Set the field value. ALL field
						 //values must be of the Object type.
             }catch (NoSuchFieldException e) {
		      e.printStackTrace();
             } catch (IllegalAccessException e) {
		      e.printStackTrace();
             }
	}

	public Object invokeMethod(Object obj, String methodName, Class[] parameterTypes,
				 Object[] parameterValues) {
	
	     Object retObject = null;
	     Class c = obj.getClass();  //Create a Class object

             try {  
		 //Get the method whose name is defined in methodName and whose
		 //parameters are defined in parameterTypes
	 	 Method method = c.getMethod(methodName, parameterTypes);
		 //Primitives are returned using their wrapper classes
		 retObject = method.invoke(obj, parameterValues);
	     } catch (NoSuchMethodException e) {
		      e.printStackTrace();
      	     } catch (IllegalAccessException e) {
		      e.printStackTrace();
      	     } catch (InvocationTargetException e) {
		      e.printStackTrace();
      	     }

	     return retObject;
	}

	public static void main(String[] args) {
	   ClassManipulator cm = new ClassManipulator();
	   session7.FlightInfo fi = (session7.FlightInfo) cm.createObject("session7.FlightInfo");
	   fi.setGate(22);
	   System.out.println(fi.getGate());  // prints 22

	   Class[] argTypes = new Class[] {String.class, int.class, int.class};
	   String flightNum = "UA123";
	   Integer gate = new Integer(25);
	   Integer numPassengers = new Integer(150);
	   Object[] argVals = new Object[] {flightNum, gate, numPassengers};
	   fi  = (session7.FlightInfo) cm.createObject("session7.FlightInfo", argTypes, argVals);
	   System.out.println(fi.getNumberOfPassengers()); //prints 150

	   // Note: can't manipulate instance variables declared as private.
	   Integer someField = (Integer)cm.getFieldValue(fi, "someField"); 
	   System.out.println(someField.intValue()); // prints 5

	   Integer newSomeFieldVal = new Integer(33);
	   cm.setFieldValue(fi, "someField", newSomeFieldVal);

	   someField = (Integer)cm.getFieldValue(fi, "someField");
           System.out.println(someField.intValue()); // prints 33

	   Class[] parameterTypes = new Class[] {};
	   Object[] parameterValues = new Object[] {};
	   String methodName = "getFlightNumber";
	   String fNum = (String)cm.invokeMethod(fi, methodName, parameterTypes,
			     			 parameterValues);

	   methodName = "setNumberOfPassengers";
	   Class[] paramTypes = new Class[] {int.class};
	   Object[] paramValues = new Object[] {new Integer(323)};

	   cm.invokeMethod(fi, methodName, paramTypes, paramValues);

	   methodName = "getNumberOfPassengers";
	   Integer numPass = (Integer)cm.invokeMethod(fi, methodName, parameterTypes,
			     			 parameterValues);
	   System.out.println(fNum + " " + numPass.intValue()); //prints UA123 150
	}
}

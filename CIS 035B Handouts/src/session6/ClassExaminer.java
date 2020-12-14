
package session6;
//Session 6
//
import java.lang.reflect.*;
import java.util.*;



public class ClassExaminer {

	public String getClassName(Object o) {

	// 1. Retrieve the Class object.
	// 2. Invoke the getName() method in that Class object.

	  Class<?> c = o.getClass();
	  return c.getName();
	}

	public Vector<String> getClassModifiers(Object o) {

	// 1. Retrieve the Class object.
	// 2. Invoke the getModifiers() method in that Class object.
	// 3. Use isPublic(), isAbstract(), and isFinal() in the Modifier class.
	
	  Vector<String> retVec = new Vector<String>();

	  Class<?> c = o.getClass();
	  int m = c.getModifiers(); // The int value returned is a combination of the 
				    // values assigned to each modifier. For example,
				    // a class declared as public (1) and final(16) 
				    // will return a value of 17.
      	  if (Modifier.isPublic(m))
		retVec.addElement("public");
      	  if (Modifier.isAbstract(m))
		retVec.addElement("abstract");
      	  if (Modifier.isFinal(m))
		retVec.addElement("final");
      	  

	  return retVec;
	}

	
	public Vector<String> getSuperClasses(Object o) {

        // 1. Retrieve the Class object.
	// 2. Use the getSuperClass() method in the Class object.

	  Vector<String> retVec = new Vector<String>();

	  Class<?> c = o.getClass();
	  Class<?> superclass = c.getSuperclass();
          while (superclass != null) {
             String className = superclass.getName();
	     retVec.addElement(className);
             c = superclass;
             superclass = c.getSuperclass();
      	  }

	  return retVec;
	}


	public Vector<String> getInterfaces(Object o) {

        // 1. Retrieve the Class object.
        // 2. Use the getInterfaces() method in the Class object.

          Vector<String> retVec = new Vector<String>();

          Class<?> c = o.getClass();
          Class<?>[] interfaces = c.getInterfaces();
	  for (int i = 0; i < interfaces.length; i++) {
              String interfaceName = interfaces[i].getName();
	      retVec.addElement(interfaceName);
          }

          return retVec;
        }

	public Vector<String> getFields(Object o) {

        // 1. Retrieve the Class object.
        // 2. Use the getFields() method in the Class object.
   	//    getFields() retrieves public fields ONLY.
	// 3. Use the getName() and getType() methods in the Field object.

          Vector<String> retVec = new Vector<String>();

          Class<?> c = o.getClass();
	  Field[] publicFields = c.getFields();
      	  for (int i = 0; i < publicFields.length; i++) {
         	  String fieldName = publicFields[i].getName();
         	  Class<?> typeClass = publicFields[i].getType();
         	  String fieldType = typeClass.getName();
         	  retVec.addElement(fieldName + " " + fieldType);
          }

	  return retVec;
	}

	public Vector<String> getMethods(Object o) {

	  // 1. Retrieve the Class object.
	  // 2. Use the getMethods() method in the Class object.
	  // 3. Use the Method class to get the modifier, name, parameters
	  //    and return type of each method. 

	  Vector<String> retVec = new Vector<String>();

	  Class<?> c = o.getClass();
	  Method[] methods = c.getMethods();
	  for (int i = 0; i < methods.length; i++) {
	     int m  = methods[i].getModifiers();
	     String methodString = Modifier.toString(m) + " ";
             methodString += methods[i].getReturnType().getName() + " ";
             methodString += methods[i].getName() + "(";
             Class<?>[] parameterTypes = methods[i].getParameterTypes();
             for (int k = 0; k < parameterTypes.length; k ++) {
                methodString += parameterTypes[k].getName() + " ";
             }
	     methodString += ")";
	     retVec.addElement(methodString);
          }
	  return retVec;
	}

	public static void main(String[] args) {
	  ClassExaminer ce = new ClassExaminer();
	  FlightInfo fi = new FlightInfo();
	  System.out.println(ce.getClassName(fi));  // prints FlightInfo

	  Vector<String> vec = ce.getClassModifiers(fi);
	  System.out.println(vec);  // prints [public]
				    // prints [] if class modifier is at the package level

	  vec = ce.getSuperClasses(fi);
	  System.out.println(vec);  // prints [java.lang.Object]

	  vec = ce.getInterfaces(fi);
	  System.out.println(vec);  // prints [Viewable]

	  vec = ce.getFields(fi);
	  System.out.println(vec);  // prints [REG_FLTNUM int, SPCL_FLTNUM int]

	  vec = ce.getMethods(fi);  // prints all method signatures
	  for (int k = 0; k < vec.size(); ++k) {
	    System.out.println(vec.elementAt(k));
	  }
	}
}

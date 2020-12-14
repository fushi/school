/**
 * John Towler
 * CIS 035B
 * Lab 2
 * Due Date: July 21, 2010
 * Date Submitted: July 21, 2010
 */

package lab2;

import java.lang.reflect.*;
import java.util.*;

/**
 * Class designed to create Car type objects from a String and a Properties
 * object.
 * @author John Towler
 * @version 1.0: July 20, 2010
 */

public class CarLotBroker {
	
	/**
	 * Instantiates a Car object, subclass based upon this.command. This method
	 * expects this.command to be in the form of "doClass", where Class is the
	 * name of a subclass of Car.
	 * @return Car object reference if successful, null otherwise.
	 */
	private Car createCarInstance(){
		String pName = this.getClass().getPackage().getName();
		String className = command.substring(2);
		
		try{
			Class<?> classDef = Class.forName(pName + "." + className);
			Constructor<?> c = classDef.getConstructor();
			return (lab2.Car) c.newInstance();
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
		}finally{
		}
		
		return null;
	}
	
	/**
	 * Invokes a method in the given object.
	 * @param obj Object containing the method.
	 * @param methodName Name of the method.
	 * @param parameterTypes Class types of the parameters of the method.
	 * @param parameterValues Values of the paramaters of the method
	 * @return The return object of the method invoked if successful, null
	 * returned if method invocation fails.
	 */
	private Object invokeMethod(Object obj, String methodName,
			Class<?>[] parameterTypes, Object[] parameterValues){
		Class<?> c = obj.getClass();
		try{
			Method m = c.getMethod(methodName, parameterTypes);
			return m.invoke(obj, parameterValues);
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		
		return null;
	}
	
	/**
	 * Checks the method for setting the price on this.car, and returns the type
	 * of the parameter for that method as a string.
	 * @return A string containing the type of the parameter for the method to
	 * set the price on this.car. If no such method is found, null is returned.
	 */
	private String getSetPriceParamType(){
		Class<?> c = car.getClass();
		
		Method[] methodArray = c.getMethods();
		
		for(Method element : methodArray){
			if (element.getName().equals(
					props.getProperty(Constants.PRICE_M_KEY))){
				Type[] t = element.getGenericParameterTypes();		
				return t[0].toString();
			}
		}
		return null;
	}
	
	/**
	 * Accepts a command and a Properties file, then instantiates a Car object.
	 * Methods of the object are then invoked to set the license plate, mileage,
	 * model, color, and price. After these are set, a report on the
	 * object is sent to stdout.
	 * @param com Command to give
	 * @param carProps Properties file
	 */
	public void carAssembler(String com, Properties carProps){
		command = com;
		props = carProps;
		car = createCarInstance();
		Class<?>[] pTypes;
		Object[] pVals;
		
		pTypes = new Class[] {String.class};
		pVals = new Object[] {props.getProperty(Constants.LP_V_KEY)};
		invokeMethod(car,
				props.getProperty(Constants.LP_M_KEY), pTypes, pVals);
		
		pTypes = new Class[] {int.class};
		pVals = new Object[] {props.get(Constants.MILEAGE_V_KEY)};
		invokeMethod(car,
				props.getProperty(Constants.MILEAGE_M_KEY), pTypes, pVals);
		
		pTypes = new Class[] {String.class};
		pVals = new Object[] {props.getProperty(Constants.MODEL_V_KEY)};
		invokeMethod(car,
				props.getProperty(Constants.MODEL_M_KEY), pTypes, pVals);
		
		pTypes = new Class[] {String.class};
		pVals = new Object[] {props.getProperty(Constants.COLOR_V_KEY)};
		invokeMethod(car,
				props.getProperty(Constants.COLOR_M_KEY), pTypes, pVals);
		
		String paramType = getSetPriceParamType();
		
		if(int.class.getName().equals(paramType)){
			pTypes = new Class[] {int.class};
			pVals = new Object[] {props.get(Constants.INDEX_V_KEY)};
			invokeMethod(car,
					props.getProperty(Constants.PRICE_M_KEY), pTypes, pVals);
		}
		
		if(double.class.getName().equals(paramType)){
			pTypes = new Class[] {double.class};
			pVals = new Object[] {props.get(Constants.PRICE_V_KEY)};
			invokeMethod(car,
					props.getProperty(Constants.PRICE_M_KEY), pTypes, pVals);
		}
		
		pTypes = null;
		pVals = null;
		System.out.println(invokeMethod(car,
				carProps.getProperty(Constants.REPORT_M_KEY), pTypes, pVals));
		
	}

	private Car car;
	private String command;
	private Properties props;
}

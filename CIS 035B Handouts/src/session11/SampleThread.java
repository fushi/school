package session11;
//Session 11
//
public class SampleThread extends Thread {

	public SampleThread() {

		System.out.println("In SampleThread's constructor");
	}

	public void run() {

	   if (this == currentThread())
	     System.out.println("currentThread() shows this thread " +
	     			"is running.");
	   if (this.isAlive())
	     System.out.println("isAlive() says this thread is alive.");

	   System.out.println("This thread will sleep for 5 secs.");
	   try {
	   	sleep(5000);
	   }catch (InterruptedException e) {
	     System.out.println("JVM woke me up in my sleep");
	   }

	   System.out.println("Finishing run() method...");
	}

	public static void main(String[] args) {
		SampleThread st = new SampleThread();
		st.start();

	        try {
	     	   sleep(3000);
	   	}catch (InterruptedException e) {}

		if (st.isAlive())
	     	  System.out.println("The thread is still alive.");

	   	//This will print before the thread finishes!
		System.out.println("Bye!");
	}
}

package session13;
//Session 13
//
public class Synchronizer {
	
	public synchronized void syncMethod(int val) {

	   int newVal = SyncDemo.total + val;
	   System.out.println ("in syncMethod()" + " Total is: " + 
			       SyncDemo.total);
	   /*
	    * This commented block can be used to give other threads
	    * the opportunity to run.
	   try {
	      Thread.sleep((int)(Math.random() * 50));
	   }catch (InterruptedException e) {}
	   */

	   // The delay line below is for demonstration purposes only.
	   // This is used to highlight the fact that only one thread 
	   // executes a synchronized method at a time.
	   // 
	   for (int k = 0; k < 80000000; ++k);

	   SyncDemo.total = newVal;

	}

	public void unSyncMethod(int val) {

	   int newVal = SyncDemo.total + val;
	   System.out.println ("in unSyncMethod()" + " Total is: " + 
			        SyncDemo.total);
	   for (int k = 0; k < 80000000; ++k);

	   SyncDemo.total = newVal;

	}

}

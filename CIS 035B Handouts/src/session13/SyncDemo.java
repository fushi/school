package session13;
//Session 13
//
public class SyncDemo {

	public static int total = 0;

	public static void main (String [] args) {

	    SyncDemo sd = new SyncDemo();
	    sd.runUnSyncThreads();
	    total =0;
	    sd.runSyncThreads();
	}

	public void runSyncThreads() {

	    Synchronizer sync = new Synchronizer();
	   boolean done = false;

	   // We will make all threads belong to one thread group
	   // for easier control.
	   ThreadGroup tg = new ThreadGroup("group");

	   //All thread references loaded in array.
	   Thread[] ft = new Thread[100];

	   for (int k = 0; k < ft.length; ++k) {
		ft[k] = new Thread(tg, new SyncThread(sync), "t");
		ft[k].start();
	   }

	   // Let all threads finish before printing total.
	   while (!done) {
		if (tg.activeCount() == 0)
			done = true;
 	   }

	   System.out.println (total);
	}

	public void runUnSyncThreads() {
	
	   Synchronizer sync = new Synchronizer();
	   boolean done = false;

	   ThreadGroup tg = new ThreadGroup("group");

	   Thread[] ft = new Thread[100];

	   for (int k = 0; k < ft.length; ++k) {
		ft[k] = new Thread(tg, new UnSyncThread(sync), "t");
		ft[k].start();
	   }

	   while (!done) {
		if (tg.activeCount() == 0)
			done = true;
 	   }

	   System.out.println (total);
	}
}

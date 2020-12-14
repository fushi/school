package session13;
//Session 13
//
public class SyncThread extends Thread {

	Synchronizer sync = null;

	public SyncThread(Synchronizer s) {
		sync = s;
	}

	public void run() {
	     sync.syncMethod(1);
	}
}

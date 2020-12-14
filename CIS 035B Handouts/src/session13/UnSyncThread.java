package session13;
//Session 13
//
public class UnSyncThread extends Thread {

	Synchronizer sync = null;

	public UnSyncThread(Synchronizer s) {
		sync = s;
	}

	public void run() {
	     sync.unSyncMethod(1);
	}
}

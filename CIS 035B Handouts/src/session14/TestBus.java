package session14;
//Session 14
//
public class TestBus {
	public void testBuses() {

	  BusDispatcher dispatcher = new BusDispatcher();

	  ThreadGroup g = new ThreadGroup("dispatchers");
	  ThreadGroup g2 = new ThreadGroup("parkers");
	  Thread dThread1 = new Thread(g, new DispatchThread(dispatcher), "t1");
	  dThread1.start();
	  Thread dThread2 = new Thread(g, new DispatchThread(dispatcher), "t2");
	  dThread2.start();

	  Bus b1 = new Bus(1, "Bush", "Texas");
	  Thread bpThread1 = new Thread(g2, new ParkThread(b1,dispatcher), "tr1");
	  bpThread1.start();

	  Bus b2 = new Bus(2, "Clinton", "Arkansas");
	  Thread bpThread2 = new Thread(g2, new ParkThread(b2,dispatcher), "tr2");
	  bpThread2.start();

	  Bus b3 = new Bus(3, "Reagan", "California");
	  Thread bpThread3 = new Thread(g2, new ParkThread(b3,dispatcher), "tr3");
	  bpThread3.start();

	  Bus b4 = new Bus(4, "Washington", "Virginia");
	  Thread bpThread4 = new Thread(g2, new ParkThread(b4,dispatcher), "tr4");
	  bpThread4.start();

	  while (g2.activeCount() > 0) {}
	  dispatcher.noMoreBuses();
	}

	public static void main(String[] args) {

	   TestBus tb = new TestBus();
	   tb.testBuses();


	}
}

package session13;
//Session 13
//
import java.util.Timer;
import java.util.TimerTask;

/**
 * Simple demo that uses java.util.Timer to schedule a task 
 * that executes every 5 seconds.
 * Note: Example taken from Java tutorial.
 */

public class Reminder {
    Timer timer;

    public Reminder(int seconds) {
        timer = new Timer();
        timer.schedule(new RemindTask(), 
			0,		 //initial delay
			seconds*1000);   //subsequent delay rate
	}

    class RemindTask extends TimerTask {
        public void run() {
            System.out.println("Good morning. This is your wakeup call.");
            //timer.cancel(); //Terminate the timer thread
        }
    }

    public static void main(String args[]) {
        new Reminder(5);
        System.out.println("Task scheduled: \n\n");
    }
}


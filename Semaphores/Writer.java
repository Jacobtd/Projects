//Jacob Doerr's Prog1
import java.util.concurrent.Semaphore;
import java.util.Random;

public class Writer extends Thread {
    private Shared shared;
    private Semaphore wmutex, M1, M2;
    private Random random = new Random();

    public Writer(Shared shared, Semaphore wmutex, Semaphore M1, Semaphore M2) {
        this.shared = shared;
        this.wmutex = wmutex;
        this.M1 = M1;
        this.M2 = M2;
    }

    @Override
    public void run() {
        try {
            System.out.println("WRITER " + this.getName() + " is ENTERING WRITER CODE");

            // Entry Section
            wmutex.acquire();
            shared.incWriteCount();
            if (shared.getWriteCount() == 1) {
                M1.acquire();
            }
            wmutex.release();
            M2.acquire();

            // Critical Section
            int sleepTime = random.nextInt(30) + 1;
            System.out.println("WRITER " + this.getName() + " is writing for " + sleepTime + " milliseconds.");
            Thread.sleep(sleepTime);
            M2.release();

            // Exit Section
            wmutex.acquire();
            shared.decWriteCount();
            if (shared.getWriteCount() == 0) {
                M1.release();
            }
            wmutex.release();

            System.out.println("WRITER " + this.getName() + " is now EXITING");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
//Jacob Doerr's Prog1
import java.util.concurrent.Semaphore;
import java.util.Random;

public class Reader implements Runnable {
    private Shared shared;
    private Semaphore rmutex, M1, M2, M3;
    private Random random = new Random();

    public Reader(Shared shared, Semaphore rmutex, Semaphore M1, Semaphore M2, Semaphore M3) {
        this.shared = shared;
        this.rmutex = rmutex;
        this.M1 = M1;
        this.M2 = M2;
        this.M3 = M3;
    }

    @Override
    public void run() {
        try {
            System.out.println("READER " + Thread.currentThread().getName() + " is ENTERING READER CODE");

            // Entry Section
            M3.acquire();
            M1.acquire();
            rmutex.acquire();
            shared.incReadCount();
            if (shared.getReadCount() == 1) {
                M2.acquire();
            }
            rmutex.release();
            M1.release();
            M3.release();

            // Critical Section
            int sleepTime = random.nextInt(30) + 1;
            System.out.println("READER " + Thread.currentThread().getName() + " is reading for " + sleepTime + " milliseconds.");
            Thread.sleep(sleepTime);

            // Exit Section
            rmutex.acquire();
            shared.decReadCount();
            if (shared.getReadCount() == 0) {
                M2.release();
            }
            rmutex.release();

            System.out.println("READER " + Thread.currentThread().getName() + " is now EXITING");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

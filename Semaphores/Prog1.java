//Jacob Doerr's Prog1
import java.util.Random;
import java.util.concurrent.Semaphore;

public class Prog1 {
    public static void main(String[] args) {
        Shared shared = new Shared(0, 0);
        static Semaphore rmutex = new Semaphore(1, true);
        static Semaphore wmutex = new Semaphore(1, true);
        static Semaphore M1 = new Semaphore(1, true);
        static Semaphore M2 = new Semaphore(1, true);
        static Semaphore M3 = new Semaphore(1, true);
        Random random = new Random();

        for (int i = 0; i < 100; i++) {
            Thread t;
            if (random.nextInt(3) == 0) {
                t = new Writer(shared, wmutex, M1, M2);
            } else {
                t = new Thread(new Reader(shared, rmutex, M1, M2, M3));
            }
            t.start();

            try {
                Thread.sleep(random.nextInt(31));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Main thread ending execution.");
    }
}
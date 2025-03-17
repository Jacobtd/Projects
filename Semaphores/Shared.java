//Jacob Doerr's Prog1
public class Shared {
    private int readCount;
    private int writeCount;

    public Shared(int readCount, int writeCount) {
        this.readCount = readCount;
        this.writeCount = writeCount;
    }

    public synchronized int getWriteCount() {
        return writeCount;
    }

    public synchronized int getReadCount() {
        return readCount;
    }

    public synchronized void incReadCount() {
        readCount++;
    }

    public synchronized void incWriteCount() {
        writeCount++;
    }

    public synchronized void decReadCount() {
        readCount--;
    }

    public synchronized void decWriteCount() {
        writeCount--;
    }
}

import java.util.concurrent.BlockingQueue;

public class Producer implements Runnable {
    private final BlockingQueue queue;

    public Producer(BlockingQueue queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        produce();
    }

    private void produce() {
        while (true) {
            double value = Math.random();
            try {
                queue.put(value);
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
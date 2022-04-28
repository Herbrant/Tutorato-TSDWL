import java.util.concurrent.BlockingQueue;

public class Consumer implements Runnable{
    private final BlockingQueue queue;

    public Consumer (BlockingQueue queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        consume();
    }

    private void consume() {
        while (true) {
            Double value;
            try {
                value = (Double) queue.take();
                System.out.println("Consumatore: " + value);
            } catch (InterruptedException e) {
                break;
            }
        }
    }

    
}

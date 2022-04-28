import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class App {
	static BlockingQueue<Double> blockingQueue = new LinkedBlockingDeque<>(5);

	public static void main(String[] args) {
		Thread p = new Thread(new Producer(blockingQueue));
		Thread c = new Thread(new Consumer(blockingQueue));

		p.start();
		c.start();
        
		try {
			p.join();
			c.join();
		}
		catch (InterruptedException e) { }
	}
}
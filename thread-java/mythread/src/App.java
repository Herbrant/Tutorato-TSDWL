public class App {
	public static void main(String[] args) {
		MyThread th1 = new MyThread("Thread 1");
		MyThread th2 = new MyThread("\t\t\t\tThread 2");
		th1.start();
		th2.start();
		try {
			th1.join();
			th2.join();
			System.out.println("main: Thread terminati\n");
		}
		catch (InterruptedException e) {
			e.printStackTrace();
			System.err.println("main: Thread interrotto\n");
		}
	}
}
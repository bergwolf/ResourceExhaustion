public class JavaThreadTest {
  public static void main(String[] args) {
    long tc = 0;
    while(true){
      new Thread(new Runnable(){
        public void run() {
          try {
            Thread.sleep((long)10000);
          } catch(InterruptedException e) {
          }
        }
      }).start();
    System.out.println("Thread Count " + ++tc);
    }
  }
}

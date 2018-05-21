public class JavaThreadTest {
  public static void main(String[] args) {
    long tc = 0;
    while(true){
      if (tc % 500 == 0) {
        try {
          Thread.sleep((long)100);
        } catch(InterruptedException e) {
        }
      }
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

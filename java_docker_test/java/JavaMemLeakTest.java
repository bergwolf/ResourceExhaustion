import java.util.Stack;
import java.util.Random;

public class JavaMemLeakTest {
  private static Random random = new Random();
  private static int i = 0;
  public static final Stack<Double> leaky = new Stack<Double>();

  public static void main(String[] args) {
    // Our static list will not free the elements here and we will simply
    // overflow the heap
    while (true) {
      leaky.add(random.nextDouble());
      // strawman conditional so we compile even with an infinite loop as this
      // will never be true
      i++;
      if (i % 10000 == 0) {
        System.out.println("i " + i);
      } else if (i < 0) {
        break;
      }
    }
  }

}

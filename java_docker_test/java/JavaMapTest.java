import java.lang.ThreadLocal;
import java.lang.reflect.*;
import java.lang.Class;
import java.util.Stack;

public class JavaMapTest {
  public static void main(String[] args) {
      Constructor<?> tlmConstructor = null;
      try {
        Class<?> clazz = Class.forName("java.lang.ThreadLocal");
        Class<?> innerClazzes[] = clazz.getDeclaredClasses();
        Class<?> innerClazz = null;
        for (Class c: innerClazzes) {
          if (c.getCanonicalName().matches("(.*)ThreadLocalMap")) innerClazz = c;
        }
        assert(innerClazz != null);
	ThreadLocal<Integer> myThreadLocal = new ThreadLocal<Integer>();
	myThreadLocal.set(new Integer(0));
        for (Constructor<?> c: innerClazz.getDeclaredConstructors()) {
          c.setAccessible(true);
          try {
            Object tlm = c.newInstance(myThreadLocal, new Integer(1));
  	    tlmConstructor = c;
	    break;
            } catch (IllegalArgumentException e) {
              continue;
          } catch (InvocationTargetException|InstantiationException|IllegalAccessException e) {
            throw new RuntimeException(e);
          }
        }
      } catch (ClassNotFoundException e) {
        throw new RuntimeException(e);
      }
    assert(tlmConstructor != null);
    Stack tls = new Stack<>();
    for(long i = 0; i <= 300000; i++) {
      try {
	ThreadLocal<Integer> myThreadLocal = new ThreadLocal<Integer>();
	myThreadLocal.set(new Integer(0));
        Object tlm = tlmConstructor.newInstance(myThreadLocal, new Integer(1));
        tls.push(tlm);
      } catch (InvocationTargetException|IllegalAccessException|InstantiationException e) {
        throw new RuntimeException(e);
      }
      System.out.println("TL Count " + i);
    }
    System.out.println("TL stack " + tls.size());
  }
}


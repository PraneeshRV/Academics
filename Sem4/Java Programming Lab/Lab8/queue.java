import java.util.*;

public class queue {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        Deque<Integer> deque = new LinkedList<>();

        for (int i = 0; i < 5; i++) {
            int num = s.nextInt();
            deque.addLast(num); 
        }
        if (!deque.isEmpty()) {
            deque.removeLast();
        }

        Iterator<Integer> iterator = deque.iterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }

        s.close();
    }
}
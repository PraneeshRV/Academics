
import java.util.*;

public class increasing {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int N = s.nextInt();

        ArrayList<Integer> list = new ArrayList<>();

        int lastAdded = Integer.MIN_VALUE;

        for (int i = 0; i < N; i++) {
            int num = s.nextInt();

            if (num > lastAdded) {
                list.add(num);
                lastAdded = num; 
            }
        }

        System.out.println(list);

        s.close();
    }
}
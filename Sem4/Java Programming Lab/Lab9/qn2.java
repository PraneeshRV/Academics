import java.util.*;
class CharCounter extends Thread {
    private String str;
    private HashMap<Character, Integer> freqMap;
    
    public CharCounter(String s) {
        str = s;
        freqMap = new HashMap<>();
    }
    
    public void run() {
        for(char c : str.toCharArray()) {
            freqMap.put(c, freqMap.getOrDefault(c, 0) + 1);
        }
        
        // Print frequency for this thread
        for(Map.Entry<Character, Integer> entry : freqMap.entrySet()) {
            System.out.print(entry.getKey() + "" + entry.getValue() + " ");
        }
        System.out.println();
    }
}
public class qn2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.nextLine(); // consume newline
        
        CharCounter[] threads = new CharCounter[n];
        
        // Create and start threads
        for(int i = 0; i < n; i++) {
            String str = sc.nextLine();
            threads[i] = new CharCounter(str);
            threads[i].start();
        }
        
        // Wait for all threads to complete
        try {
            for(CharCounter thread : threads) {
                thread.join();
            }
        } catch(InterruptedException e) {
            System.out.println("Thread interrupted");
        }
        
        sc.close();
    }
}

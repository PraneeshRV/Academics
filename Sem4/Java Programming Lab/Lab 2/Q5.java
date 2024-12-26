import java.util.Scanner;

class Occurence {
   
    public int count(String str, char ch) {
        int occurrences = 0;
       
        for (char c : str.toCharArray()) {
            if (c == ch) occurrences++;  
        }
        return occurrences;
    }
}

public class Q5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
       
        System.out.print("Enter a string: ");
        String str = sc.nextLine();

        
        System.out.print("Enter the character to search for: ");
        char ch = sc.nextLine().charAt(0); 

        
        Occurence occ = new Occurence();
        
        sc.close();
        System.out.println("Occurrences: " + occ.count(str, ch));
    }
}

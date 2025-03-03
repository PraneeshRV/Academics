import java.util.*;
public class qn13 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String match = scanner.nextLine();
        int peterScore = 0;
        int horejsiScore = 0;
        for (char point : match.toCharArray()) {
            if (point == '1') {
                peterScore++;
            } else if (point == '0') {
                horejsiScore++;
            }
            if (peterScore >= 11 && horejsiScore < 10) {
                System.out.println("Win");
                return;
            }
            if (horejsiScore >= 11 && peterScore < 10) {
                System.out.println("Lose");
                return;
            }
            if (peterScore >= 10 && horejsiScore >= 10) {
                if (Math.abs(peterScore - horejsiScore) >= 2) {
                    if (peterScore > horejsiScore) {
                        System.out.println("Win");
                    } else {
                        System.out.println("Lose");
                    }
                    
                    return;
                }
            }
        }
    }
}
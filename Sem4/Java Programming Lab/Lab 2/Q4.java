import java.util.Scanner;

class Innings {
    private String battingTeam;
    private int runs;

    
    public void setBattingTeam(String team) {
        this.battingTeam = team;
    }

    public void setRuns(int runs) {
        this.runs = runs;
    }

   
    public String getBattingTeam() {
        return battingTeam;
    }

    public int getRuns() {
        return runs;
    }

    
    public void display(int inningsNumber) {
        System.out.println("Innings Details "+ inningsNumber);
        System.out.println("Batting Team: " + battingTeam);
        System.out.println("Runs Scored: " + runs);
        System.out.println();
    }
}

public class Q4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        
        Innings[] innings = new Innings[2];

        for (int i = 0; i < 2; i++) {
            innings[i] = new Innings();

           
            System.out.print("Enter the name of the batting team for innings " + (i + 1) + ": ");
            innings[i].setBattingTeam(sc.nextLine());

           
            System.out.print("Enter the runs scored by the team in innings " + (i + 1) + ": ");
            innings[i].setRuns(sc.nextInt());
            sc.nextLine(); 
        }

        sc.close();
        for (int i = 0; i < 2; i++) {
            innings[i].display(i + 1);
        }
    }
}

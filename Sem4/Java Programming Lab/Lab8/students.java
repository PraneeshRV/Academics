import java.util.*;

class Student {
    private int rno;
    private String name;
    private int m1, m2, m3;
    private double avg;

    public Student() {}

    public Student(int rno, String name, int m1, int m2, int m3) {
        this.rno = rno;
        this.name = name;
        this.m1 = m1;
        this.m2 = m2;
        this.m3 = m3;
        calculateAverage(); }

    public int getRno() { return rno;}

    public void setRno(int rno) {this.rno = rno;}

    public String getName() { return name; }

    public void setName(String name) {this.name = name;}

    public int getm1() { return m1; }

    public void setm1(int m1) {this.m1 = m1;}

    public int getm2() { return m2;}

    public void setm2(int m2) { this.m2 = m2; }

    public int getm3() { return m3;}

    public void setm3(int m3) { this.m3 = m3;}

    public double getAvg() { return avg; }

    public void calculateAverage() { avg = (m1 + m2 + m3) / 3.0; }

    public String toString() {
        return String.format("%-20d%-20s%-20.1f", rno, name, avg);
    }
}

public class students {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int N = s.nextInt();
        s.nextLine(); 
        ArrayList<Student> studentList = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            int rno = s.nextInt();
            s.nextLine(); 
            String name = s.nextLine();
            int m1 = s.nextInt();
            int m2 = s.nextInt();
            int m3 = s.nextInt();
            s.nextLine(); 
            Student student = new Student(rno, name, m1, m2, m3);
            studentList.add(student);
        }

        Collections.sort(studentList, (s1, s2) -> Double.compare(s1.getAvg(), s2.getAvg()));

        System.out.println("Roll No             Name                Average");
        System.out.println("-------------------------------------------------------");

        for (Student student : studentList) {
            System.out.println(student);
        }

        s.close();
    }
}
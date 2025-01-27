
interface ShapeCalculator {
    void calc(int n); 
}


class Square implements ShapeCalculator {
    @Override
    public void calc(int n) {
        int area = n * n; 
        int perimeter = 4 * n; 
        System.out.println(area + " " + perimeter);
    }
}


class Circle implements ShapeCalculator {
    @Override
    public void calc(int n) {
        double area = Math.PI * n * n; 
        double perimeter = 2 * Math.PI * n; 
        System.out.println(String.format("%.2f %.2f", area, perimeter));
    }
}

public class q1{
    public static void main(String[] args) {
        int n = 8;
        Square square = new Square();
        Circle circle = new Circle();
        
        
        square.calc(n);
        circle.calc(n);
    }
}

    abstract class Shape {
        abstract void rectangleArea(double length, double breadth);
        abstract void squareArea(double side);
        abstract void circleArea(double radius);
    }

    class Area extends Shape {
        void rectangleArea(double length, double breadth) {
            System.out.println(length * breadth);
        }
    
        void squareArea(double side) {
            System.out.println(side * side);
        }
    
        void circleArea(double radius) {
            System.out.println(String.format("%.2f", Math.PI * radius * radius));
        }
    }

    class qn1 {
        public static void main(String[] args) {
            java.util.Scanner sc = new java.util.Scanner(System.in);
        
            System.out.println("Enter length:");
            double length = sc.nextDouble();
            System.out.println("Enter breadth:");
            double breadth = sc.nextDouble();
            System.out.println("Enter side:");
            double side = sc.nextDouble();
            System.out.println("Enter radius:");
            double radius = sc.nextDouble();
        
            Area area = new Area();
            area.rectangleArea(length, breadth);
            area.squareArea(side);
            area.circleArea(radius);
        
            sc.close();
        }
    }
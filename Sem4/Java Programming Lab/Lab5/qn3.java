  import java.util.Arrays;
  import java.util.Scanner;
  abstract class math {
      abstract void rectanglePerimeter();
      abstract void squarePerimeter();
      abstract void trianglePerimeter();
      abstract void trapezoidPerimeter();
      abstract void circlePerimeter();
  }
  class perimeter extends math {
      private double rectPerimeter, squarePerimeter, trianglePerimeter, trapezoidPerimeter, circlePerimeter;
      private Scanner sc = new Scanner(System.in);
      void rectanglePerimeter() {
          System.out.println("Enter length and breadth of rectangle:");
          double length = sc.nextDouble();
          double breadth = sc.nextDouble();
          rectPerimeter = 2 * (length + breadth);
          System.out.println("Rectangle Perimeter:");
          System.out.println((int)rectPerimeter);
      }
      void squarePerimeter() {
          System.out.println("Enter side of square:");
          double side = sc.nextDouble();
          squarePerimeter = 4 * side;
          System.out.println("Square Perimeter:");
          System.out.println((int)squarePerimeter);
      }
      void trianglePerimeter() {
          System.out.println("Enter three sides of triangle:");
          double side1 = sc.nextDouble();
          double side2 = sc.nextDouble();
          double side3 = sc.nextDouble();
          trianglePerimeter = side1 + side2 + side3;
          System.out.println("Triangle Perimeter:");
          System.out.println((int)trianglePerimeter);
      }
      void trapezoidPerimeter() {
          System.out.println("Enter four sides of trapezoid:");
          double side1 = sc.nextDouble();
          double side2 = sc.nextDouble();
          double side3 = sc.nextDouble();
          double side4 = sc.nextDouble();
          trapezoidPerimeter = side1 + side2 + side3 + side4;
          System.out.println("Trapezoid Perimeter:");
          System.out.println((int)trapezoidPerimeter);
      }
    
      void circlePerimeter() {
          System.out.println("Enter radius of circle:");
          double radius = sc.nextDouble();
          circlePerimeter = 2 * Math.PI * radius;
          System.out.println("Circle Perimeter:");
          System.out.println((int)circlePerimeter);
      }
    
      void calculateSum() {
          double sum = rectPerimeter + squarePerimeter + trianglePerimeter + trapezoidPerimeter + circlePerimeter;
          System.out.println("Sum of all perimeters:");
          System.out.println((int)sum);
      }
    
      void sortPerimeter() {
          double[] perimeters = {rectPerimeter, squarePerimeter, trianglePerimeter, trapezoidPerimeter, circlePerimeter};
          Arrays.sort(perimeters);
          System.out.println("Sorted perimeters:");
          for(int i = 0; i < perimeters.length; i++) {
              System.out.print((int)perimeters[i] + " ");
          }
      }
  }

  public class qn3 {
      public static void main(String[] args) {
          perimeter p = new perimeter();
          p.rectanglePerimeter();
          p.squarePerimeter();
          p.trianglePerimeter();
          p.trapezoidPerimeter();
          p.circlePerimeter();
          p.calculateSum();
          p.sortPerimeter();
      }
  }

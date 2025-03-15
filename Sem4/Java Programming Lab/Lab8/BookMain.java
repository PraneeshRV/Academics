import java.util.*;
class Book {
    private int id;
    private String name;
    private String author;
    private String publisher;
    private int quantity;

    public Book() {}

    public Book(int id, String name, String author, String publisher, int quantity) {
        this.id = id;
        this.name = name;
        this.author = author;
        this.publisher = publisher;
        this.quantity = quantity;
    }

    public int getId() {return id;}
    public void setId(int id) {this.id = id;}

    public String getName() {return name;}
    public void setName(String name) {this.name = name;}

    public String getAuthor() {return author;}
    public void setAuthor(String author) {this.author = author;}

    public String getPublisher() {return publisher;}
    public void setPublisher(String publisher) {this.publisher = publisher;}

    public int getQuantity() {return quantity;}
    public void setQuantity(int quantity) {this.quantity = quantity;}

    public String toString() {
        return id + " " + name + " " + author + " " + publisher + " " + quantity;}
}
public class BookMain {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        sc.nextLine(); 
        LinkedHashSet<Book> bookSet = new LinkedHashSet<>();

        for (int i = 0; i < N; i++) {
            int id = sc.nextInt();
            sc.nextLine(); 
            String name = sc.nextLine();
            String author = sc.nextLine();
            String publisher = sc.nextLine();
            int quantity = sc.nextInt();
            sc.nextLine(); 
            Book book = new Book(id, name, author, publisher, quantity);
            bookSet.add(book);
        }

        String searchName = sc.nextLine();
        for (Book book : bookSet) {
            System.out.println(book);
        }
        boolean found = false;
        for (Book book : bookSet) {
            if (book.getName().equalsIgnoreCase(searchName)) {
                found = true;
                break;
            }
        }

        if (found) {
            System.out.println(searchName + " is present in the set");
        } else {
            System.out.println(searchName + " is not present in the set");
        }

        sc.close();
    }
}
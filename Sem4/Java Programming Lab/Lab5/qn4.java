import java.util.Scanner;
class TicketBooking {
    private String stageEvent;
    private String customer;
    private Integer noOfSeats;
    public TicketBooking() {
    }
    public TicketBooking(String stageEvent, String customer, Integer noOfSeats) {
        this.stageEvent = stageEvent;
        this.customer = customer;
        this.noOfSeats = noOfSeats;
    }
    public String getStageEvent() {
        return stageEvent;
    }
    public void setStageEvent(String stageEvent) {
        this.stageEvent = stageEvent;
    }
    public String getCustomer() {
        return customer;
    }
    public void setCustomer(String customer) {
        this.customer = customer;
    }
    public Integer getNoOfSeats() {
        return noOfSeats;
    }
    public void setNoOfSeats(Integer noOfSeats) {
        this.noOfSeats = noOfSeats;
    }
    public void makePayment(double amount) {
        System.out.println("Stage event:" + stageEvent);
        System.out.println("Customer:" + customer);
        System.out.println("Number of seats:" + noOfSeats);
        System.out.printf("Amount %.1f paid in cash\n", amount);
    }
    public void makePayment(double amount, String walletNumber) {
        System.out.println("Stage event:" + stageEvent);
        System.out.println("Customer:" + customer);
        System.out.println("Number of seats:" + noOfSeats);
        System.out.printf("Amount %.1f paid using wallet number %s\n", amount, walletNumber);
    }
    public void makePayment(String holderName, double amount, String cardType, String ccv) {
        System.out.println("Stage event:" + stageEvent);
        System.out.println("Customer:" + customer);
        System.out.println("Number of seats:" + noOfSeats);
        System.out.println("Holder name:" + holderName);
        System.out.printf("Amount %.1f paid using %s card\n", amount, cardType);
        System.out.println("CCV:" + ccv);
    }
}

public class qn4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter ticket booking details (stageEvent,customer,noOfSeats):");
        String[] bookingDetails;
        while (true) {
            bookingDetails = sc.nextLine().split(",");
            if (bookingDetails.length == 3) {
                break;
            } else {
                System.out.println("Invalid input. Please enter details in the format: stageEvent,customer,noOfSeats");
            }
        }
        TicketBooking booking = new TicketBooking(bookingDetails[0], bookingDetails[1], Integer.parseInt(bookingDetails[2]));
        System.out.println("Enter payment mode (1-Cash, 2-Wallet, 3-Credit Card):");
        int paymentMode = sc.nextInt();
        switch(paymentMode) {
            case 1:
                System.out.println("Enter amount:");
                double cashAmount = sc.nextDouble();
                booking.makePayment(cashAmount);
                break;
            case 2:
                System.out.println("Enter amount:");
                double walletAmount = sc.nextDouble();
                System.out.println("Enter wallet number:");
                sc.nextLine();
                String walletNumber = sc.nextLine();
                booking.makePayment(walletAmount, walletNumber);
                break;
            case 3:
                System.out.println("Enter card holder name:");
                sc.nextLine();
                String holderName = sc.nextLine();
                System.out.println("Enter amount:");
                double cardAmount = sc.nextDouble();
                System.out.println("Enter card type:");
                sc.nextLine();
                String cardType = sc.nextLine();
                System.out.println("Enter CCV:");
                String ccv = sc.nextLine();
                booking.makePayment(holderName, cardAmount, cardType, ccv);
                break;
            default:
                System.out.println("Invalid choice");
        }
        sc.close();
    }

    public int minFrontMoves(int[] arr) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'minFrontMoves'");
    }
}

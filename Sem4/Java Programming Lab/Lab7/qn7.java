import java.util.*;
public class qn7 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String mobileNumber = scanner.nextLine();
        scanner.close();
        if (isValidMobileNumber(mobileNumber)) {
            System.out.println("Mobile number valid");
        } else {
            System.out.println("Mobile number invalid");
        }
    }

    public static boolean isValidMobileNumber(String mobileNumber) {
        if (mobileNumber.indexOf("+91") == 0) {
            StringBuilder remainingNumber = new StringBuilder(mobileNumber.substring(3));
            if (remainingNumber.length() == 10 &&
                    isAllDigits(remainingNumber.toString())) {
                return true;
            }
        }
        return false;
    }

    public static boolean isAllDigits(String str) {
        for (int i = 0; i < str.length(); i++) {
            if (!Character.isDigit(str.charAt(i))) {
                return false;
            }
        }
        return true;
    }
}
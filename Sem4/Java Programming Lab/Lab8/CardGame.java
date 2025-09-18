import java.util.*;

class Cards {
    private String symbol;
    private int number;

    public Cards(String symbol, int number) {
        this.symbol = symbol;
        this.number = number;
    }

    public String getSymbol() {
        return symbol;
    }

    public int getNumber() {
        return number;
    }

    public String toString() {
        return symbol + " " + number;
    }
}

public class CardGame {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int N = s.nextInt();
        s.nextLine(); 
        List<Cards> cardsList = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            String symbol = s.nextLine();
            int number = Integer.parseInt(s.nextLine());

            cardsList.add(new Cards(symbol, number));
        }

        List<String> distinctSymbols = new ArrayList<>();

        for (Cards card : cardsList) {
            if (!distinctSymbols.contains(card.getSymbol())) {
                distinctSymbols.add(card.getSymbol());
            }
        }

        Collections.sort(distinctSymbols);

        System.out.println("Distinct Symbols are:");
        System.out.println(String.join(" ", distinctSymbols));

        for (String symbol : distinctSymbols) {
            System.out.println("Cards in " + symbol + " Symbol:");

            List<Cards> cardsInSymbol = new ArrayList<>();
            int sumOfNumbers = 0;

            for (Cards card : cardsList) {
                if (card.getSymbol().equals(symbol)) {
                    cardsInSymbol.add(card);
                    sumOfNumbers += card.getNumber();
                }
            }

            for (Cards card : cardsInSymbol) {
                System.out.println(card);
            }

            System.out.println("Number of Cards: " + cardsInSymbol.size());
            System.out.println("Sum of Numbers: " + sumOfNumbers);
        }

        s.close();
    }
}

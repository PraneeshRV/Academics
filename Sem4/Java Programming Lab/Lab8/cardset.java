import java.util.*;

class Card {
    String symbol;
    int number;

    public Card(String symbol, int number) {
        this.symbol = symbol;
        this.number = number;
    }

    public String toString() {
        return symbol + " " + number;
    }
}

public class cardset {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        ArrayList<Card> cardList = new ArrayList<>();

        int u = 0;
        int cardCount = 0;

        while (u < 4) {
            String symbol = s.nextLine();
            int number = Integer.parseInt(s.nextLine());

            boolean isUnique = true;
            for (Card card : cardList) {
                if (card.symbol.equalsIgnoreCase(symbol)) {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique) {
                cardList.add(new Card(symbol, number));
                u++;
            }

            cardCount++;
        }

        System.out.println("Four symbols gathered in " + cardCount + " cards");

        Collections.sort(cardList, (c1, c2) -> c1.symbol.compareToIgnoreCase(c2.symbol));

        System.out.println("Cards in Set are:");
        for (Card card : cardList) {
            System.out.println(card);
        }

        s.close();
    }
}
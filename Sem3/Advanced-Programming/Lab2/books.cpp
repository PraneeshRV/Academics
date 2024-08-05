#include <iostream>
#include <string> 
using namespace std;

class Book{
    private:
     int bookID;
     string title;
     string author;
     float price;

    public:
    Book(){
        bookID=1000,
        title="null",
        author="null",
        price=0;

    }
    Book(int _bookID, string _title, string _author, float _price){
        bookID = _bookID,
        title = _title,
        author = _author,
        price = _price;
    }

    void displayDetails(){
        cout << "Book ID: " << bookID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: " << price << endl;
    }

    float calculatePrice(){
        return price;
    }
    float calculatePrice(float discount){
        return price - (price*discount/100);
    }
    void updateDetails(int _id) {
        bookID = _id;
    }   
    void updatePrice(float _p) {
        price = _p;
    }
    void updateDetails( string _t, string _a) {
        title = _t;
        author = _a;
    }
        
};

int main (){
    
    Book book0;
    book0.displayDetails();
    cout <<endl;

    Book book1(1001,"PonniyinSelvan","Kalki",699);
    book1.displayDetails();

    cout << "Price without discount: " << book1.calculatePrice() << endl;
    cout << "Price with 25% discount: " << book1.calculatePrice(25) << endl<<endl;
    
    book0.updateDetails(1002);
    book0.updatePrice(799.50);
    book0.updateDetails("Percy Jackson","Rick Riordan");
    book0.displayDetails();
    cout <<endl;
    
    cout << "Price without discount: " << book1.calculatePrice() << endl;
    cout << "Price with 25% discount: " << book1.calculatePrice(25) << endl <<endl;

    return 0;
}
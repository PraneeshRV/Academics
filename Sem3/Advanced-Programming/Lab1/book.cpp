    #include <iostream>
    using namespace std;

    class Book{
        private:

        string bookname;
        string authorname;
        string edition;
        int published_year;
        long isbn_no;
        string isbn_no_v;
        float price;
        string genre;
        int isbnvalid;
        long int sum = 0;
        long isbbn = isbn_no;
        bool validateISBN(){
                    
                    for (int i=0;i<11;i++){
                    sum = sum + (isbbn%10) * i;
                    isbbn = isbbn/10;
                    
                }
                if (sum % 11 ==0)
                    return true;
                    else 
                    return false;
            }

        public:

        void displayDetails(){
            cout << "bookname:" << bookname<<endl;
            cout << "authorname:" << authorname<<endl;
            cout << "published on :" << published_year<<endl;
            cout << edition << " edition"<<endl;
            if (validateISBN() == true)
            cout<<"ISBN number:" << isbn_no << endl;
            else
            cout <<"Invalid ISBN";
            cout << "price:" << price<<endl;
            cout << "Genre:" << genre<<endl;
        }
            Book(string _bookname,string _authorname,string _edition,int _published_year, long _isbn_no, float _price,string _genre ){
                            bookname = _bookname;
                            authorname = _authorname;
                            edition = _edition;
                            published_year = _published_year;
                            isbn_no = _isbn_no;
                            price = _price;
                            genre = _genre;
            }
    };

    int main(){
        Book b1 ("Concepts of Physics part-2","Verma HC", "Eleventh", 2023,2123456802,599.00,"Physics");
        b1.displayDetails();
        return 0;
    }
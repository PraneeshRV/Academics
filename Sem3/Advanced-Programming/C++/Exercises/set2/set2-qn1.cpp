#include <iostream>
using namespace std;

class Time {
private:
    int hrs;
    int mins;

public:
    Time(int _h = 0, int _m = 0){
        hrs=_h;
        mins=_m;
        }

    bool operator==(const Time& other) const {
        return (hrs == other.hrs && mins == other.mins);
    }

    void display() const {
        cout << hrs << ":" << (mins < 10 ? "0" : "") << mins;
    }
};

int main() {
    Time t1(14, 30);
    Time t2(12, 3);
    cout << "t1 = ";
    t1.display();
   cout << endl;
    
    cout << "t2 = ";
    t2.display();

cout << endl<<"the times t1 & t2 are "<< (t1 == t2 ? "Equal" : "Not Equal") << endl;

    return 0;
}

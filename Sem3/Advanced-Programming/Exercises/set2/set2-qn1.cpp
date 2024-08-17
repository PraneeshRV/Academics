#include <iostream>

class Time {
private:
    int hours;
    int minutes;

public:
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}

    bool operator==(const Time& other) const {
        return (hours == other.hours && minutes == other.minutes);
    }

    void display() const {
        std::cout << hours << ":" << (minutes < 10 ? "0" : "") << minutes;
    }
};

int main() {
    Time t1(14, 30);
    Time t2(14, 30);
    Time t3(15, 45);

    std::cout << "t1 = ";
    t1.display();
    std::cout << std::endl;

    std::cout << "t2 = ";
    t2.display();
    std::cout << std::endl;

    std::cout << "t3 = ";
    t3.display();
    std::cout << std::endl;

    std::cout << "t1 == t2: " << (t1 == t2 ? "Equal" : "Not Equal") << std::endl;
    std::cout << "t1 == t3: " << (t1 == t3 ? "Equal" : "Not Equal") << std::endl;

    return 0;
}

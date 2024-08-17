#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    double x;
    double y;

public:

    Vector(double x = 0, double y = 0) : x(x), y(y) {}

    double dotProduct(const Vector& other) const {
        return (x * other.x) + (y * other.y);
    }


    double crossProduct(const Vector& other) const {
        return (x * other.y) - (y * other.x);
    }

    double magnitude() const {
        return sqrt((x * x) + (y * y));
    }

    void print() const {
        cout << "(" << x << ", " << y << ")" <<endl;
    }
};

int main() {
    Vector v1(3.0, 7.0);
    Vector v2(8.0, 4.0);

    double dot = v1.dotProduct(v2);
    cout << "v1 . v2: " << dot <<endl;

    double cross = v1.crossProduct(v2);
    cout << "v1 x v2: " << cross <<endl;

    double magv1 = v1.magnitude();
    cout << "v1 magnitude: " << magv1 <<endl;
    double magv2 = v2.magnitude();
    cout << "v2 magnitude: " << magv2 <<endl;
    cout<<"vector v1:"<<endl;
    v1.print();
    cout<<"vector v2:"<<endl;
    v2.print();

    return 0;
}
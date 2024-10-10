#include <iostream>
#include <cmath>
using namespace std;

class Poly {
private:
    int degree;
    int coeff[100];

public:

    Poly(int deg) {
        degree = deg;
        for (int i = 0; i <= degree; i++) {
            coeff[i] = 0;
        }
    }

    Poly(int deg, int coef[]) {
        degree = deg;
        for (int i = 0; i <= degree; i++) {
            coeff[i] = coef[i];
        }
    }

    Poly add(const Poly& other) const {
        int maxDeg = max(degree, other.degree);
        int resCoef[10] = {0};

        for (int i = 0; i <= maxDeg; i++) {
            if (i <= degree) {
                resCoef[i] += coeff[i];
            }
            if (i <= other.degree) {
                resCoef[i] += other.coeff[i];
            }
        }

        return Poly(maxDeg, resCoef);
    }

    Poly subtract(const Poly& other) const {
        int maxDeg = max(degree, other.degree);
        int resCoef[10] = {0};

        for (int i = 0; i <= maxDeg; i++) {
            if (i <= degree) {
                resCoef[i] += coeff[i];
            }
            if (i <= other.degree) {
                resCoef[i] -= other.coeff[i];
            }
        }

        return Poly(maxDeg, resCoef);
    }

    int evaluate(int x) const {
        int result = 0;
        for (int i = 0; i <= degree; i++) {
            result += coeff[i] * pow(x, i);
        }
        return result;
    }

    void print() const {
        for (int i = degree; i >= 0; i--) {
            if (coeff[i] != 0) {
                if (i != degree && coeff[i] > 0) {
                    cout << " + ";
                }
                if (coeff[i] < 0) {
                    cout << " - ";
                    if (abs(coeff[i]) != 1 || i == 0) {
                        cout << abs(coeff[i]);
                    }
                } else {
                    if (coeff[i] != 1 || i == 0) {
                        cout << coeff[i];
                    }
                }
                if (i > 0) {
                    cout << "x";
                    if (i > 1) {
                        cout << "^" << i;
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int co1[] = {1, 2, 3}; 
    int co2[] = {3, 4};    

    Poly p1(2, co1);
    Poly p2(1, co2);

    cout<<"p1"<<endl;
    p1.print();

    cout<<"p2"<<endl;
    p2.print();

    Poly p3 = p1.add(p2);
    cout<<"p1+p2"<<endl;
    p3.print();

    Poly p4 = p1.subtract(p2);
    cout<<"p1-p2"<<endl;
    p4.print();

    int value = p2.evaluate(4);
    cout << "p2 at x=4"<<endl<<value;

    return 0;
}

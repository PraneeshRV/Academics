#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
private:
    int degree;
    int *coefficients;

public:
    Polynomial(int deg) {
        degree = deg;
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = 0;
        }
    }

    Polynomial(int deg, int coeffs[]) {
        degree = deg;
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    Polynomial add(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; i++) {
            if (i <= degree) {
                result.coefficients[i] += coefficients[i];
            }
            if (i <= other.degree) {
                result.coefficients[i] += other.coefficients[i];
            }
        }

        return result;
    }

    Polynomial subtract(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; i++) {
            if (i <= degree) {
                result.coefficients[i] += coefficients[i];
            }
            if (i <= other.degree) {
                result.coefficients[i] -= other.coefficients[i];
            }
        }

        return result;
    }

    int evaluate(int x) const {
        int result = 0;
        for (int i = 0; i <= degree; i++) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    void print() const {
        for (int i = degree; i >= 0; i--) {
            if (coefficients[i] != 0) {
                if (i != degree && coefficients[i] > 0) {
                    cout << " + ";
                }
                if (coefficients[i] < 0) {
                    cout << " - ";
                    if (abs(coefficients[i]) != 1 || i == 0) {
                        cout << abs(coefficients[i]);
                    }
                } else {
                    if (coefficients[i] != 1 || i == 0) {
                        cout << coefficients[i];
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
    int coeffs1[] = {1, 2, 3}; 
    int coeffs2[] = {3, 4};    

    Polynomial p1(2, coeffs1);
    Polynomial p2(1, coeffs2);

    cout << "Polynomial p1: ";
    p1.print();

    cout << "Polynomial p2: ";
    p2.print();

    Polynomial p3 = p1.add(p2);
    cout << "p1 + p2: ";
    p3.print();

    Polynomial p4 = p1.subtract(p2);
    cout << "p1 - p2: ";
    p4.print();

    int value = p1.evaluate(2);
    cout << "p1 evaluated at x = 2: " << value << endl;

    return 0;
}

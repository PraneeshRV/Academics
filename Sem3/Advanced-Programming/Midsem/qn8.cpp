#include <iostream>
using namespace std;

// Class to represent a complex rational number
class ComplexRational {
private:
    int numeratorReal;
    int denominatorReal;
    int numeratorImaginary;
    int denominatorImaginary;

public:
    // Constructor to initialize the complex rational number
    ComplexRational(int _numeratorReal, int _denominatorReal, int _numeratorImaginary, int _denominatorImaginary) {
        numeratorReal = _numeratorReal;
        denominatorReal = _denominatorReal;
        numeratorImaginary = _numeratorImaginary;
        denominatorImaginary = _denominatorImaginary;
    }

    // Overloaded addition operator
    ComplexRational operator+(const ComplexRational& other) const {
        int nR = numeratorReal * other.denominatorReal + other.numeratorReal * denominatorReal;
        int dR = denominatorReal * other.denominatorReal;
        int nI = numeratorImaginary * other.denominatorImaginary + other.numeratorImaginary * denominatorImaginary;
        int dI = denominatorImaginary * other.denominatorImaginary;
        if (dR == 0 || dI == 0) {
            return ComplexRational(0, 0, 0, 0); // Represents undefined
        }
        return ComplexRational(nR, dR, nI, dI);
    }

    // Overloaded subtraction operator
    ComplexRational operator-(const ComplexRational& other) const {
        int nR = numeratorReal * other.denominatorReal - other.numeratorReal * denominatorReal;
        int dR = denominatorReal * other.denominatorReal;
        int nI = numeratorImaginary * other.denominatorImaginary - other.numeratorImaginary * denominatorImaginary;
        int dI = denominatorImaginary * other.denominatorImaginary;
        if (dR == 0 || dI == 0) {
            return ComplexRational(0, 0, 0, 0); // Represents undefined
        }
        return ComplexRational(nR, dR, nI, dI);
    }

    // Overloaded multiplication operator
    ComplexRational operator*(const ComplexRational& other) const {
        int nR = numeratorReal * other.numeratorReal * denominatorImaginary * other.denominatorImaginary + 
                               numeratorImaginary * other.numeratorImaginary * denominatorReal * other.denominatorReal;
        int dR = denominatorReal * other.denominatorReal * denominatorImaginary * other.denominatorImaginary;
        int nI = numeratorReal * other.numeratorImaginary * denominatorImaginary * other.denominatorReal + 
                                    numeratorImaginary * other.numeratorReal * denominatorReal * other.denominatorImaginary;
        int dI = denominatorReal * other.denominatorReal * denominatorImaginary * other.denominatorImaginary;
        if (dR == 0 || dI == 0) {
            return ComplexRational(0, 0, 0, 0); // Represents undefined
        }
        return ComplexRational(nR, dR, nI, dI);
    }

    // Overloaded output operator
    void operator<<(const ComplexRational &other){
        if (other.denominatorReal == 0 || other.denominatorImaginary == 0) {
            cout << "undefined as denominator is zero";
        } else {
            cout << "(" << other.numeratorReal << "/" << other.denominatorReal << ") + i(" 
               << other.numeratorImaginary << "/" << other.denominatorImaginary << ")";
        }
    }
};

int main() {
        ComplexRational c1(1, 1, 1, 1);
        ComplexRational c2(1, 1, 1, 1);
        ComplexRational c3(1, 1, 1, 1);

        while (true) {
            int nr1, dr1, ni1, di1, nr2, dr2, ni2, di2, opt;

            // Input for the first complex rational number
            cout << "Enter non-zero values for the first complex rational number:" << endl;
            cout << "Numerator Real: ";
            cin >> nr1;
            cout << "Denominator Real: ";
            cin >> dr1;
            while (dr1 == 0) {
                cout << "Denominator Real cannot be zero. Please enter a non-zero value: ";
                cin >> dr1;
            }
            cout << "Numerator Imaginary: ";
            cin >> ni1;
            cout << "Denominator Imaginary: ";
            cin >> di1;
            while (di1 == 0) {
                cout << "Denominator Imaginary cannot be zero. Please enter a non-zero value: ";
                cin >> di1;
            }

            // Input for the second complex rational number
            cout << "Enter non-zero values for the second complex rational number:" << endl;
            cout << "Numerator Real: ";
            cin >> nr2;
            cout << "Denominator Real: ";
            cin >> dr2;
            while (dr2 == 0) {
                cout << "Denominator Real cannot be zero. Please enter a non-zero value: ";
                cin >> dr2;
            }
            cout << "Numerator Imaginary: ";
            cin >> ni2;
            cout << "Denominator Imaginary: ";
            cin >> di2;
            while (di2 == 0) {
                cout << "Denominator Imaginary cannot be zero. Please enter a non-zero value: ";
                cin >> di2;
            }

            // Create ComplexRational objects with user input
            c1 = ComplexRational(nr1, dr1, ni1, di1);
            c2 = ComplexRational(nr2, dr2, ni2, di2);

            // Display menu options
            cout << "Enter Your option:" << endl;
            cout << "1. Display details" << endl;
            cout << "2. Add" << endl;
            cout << "3. Subtract" << endl;
            cout << "4. Multiply" << endl;
            cout << "5. Exit" << endl;
            cin >> opt;

            // Process user's choice
            switch (opt) {
                case 1:
                    cout << "First complex rational number: "; 
                    c1<< c1;
                    cout<<endl;
                    cout << "Second complex rational number: "; 
                    c1<< c2;
                    cout<<endl;
                    break;
                case 2:
                    c3 = c1 + c2;
                    cout << "addition: ";
                    c3<<c3;
                    cout<<endl;
                    break;
                case 3:
                    c3 = c1 - c2;
                    cout << "subtraction: ";
                    c3<< c3;
                    cout<<endl;
                    break;
                case 4:
                    c3 = c1 * c2;
                    cout << "multiplication: " ;
                    c3<< c3;
                    cout<<endl;
                    break;
                case 5:
                    cout << "Exiting...." << endl;
                    break;
                default:
                    cout << "Please enter a valid input" << endl;
            }

            cout << "\nDo you want to try for 2 other numbers? (Y/N): ";
            char choice;
            cin >> choice;
            if (choice == 'N' || choice == 'n') {
                cout << "Exiting...." << endl;
                break;
            }
        } while (true);

        return 0;
}
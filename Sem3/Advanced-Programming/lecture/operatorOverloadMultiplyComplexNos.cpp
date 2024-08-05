#include <iostream>
using namespace std;

class Complex{
    private:
    int real;
    int img;

    public:

    Complex (int r,int i){
        real = r;
        img  = i;
    }

    Complex operator*(Complex const &other){
        return Complex((real*other.real)-(img*other.img),(real*other.img)+(img*other.real));
    }

    void print(){
        cout<<real<<"+"<<img<<"i"<<endl;
    }

};

int main(){
    Complex c1(3,5);
    Complex c2(2,3);
    c1.print();
    c2.print();
    Complex c3 = c1*c2;
    c3.print();
    return 0;
}
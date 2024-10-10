#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
    string name;

public:

   void makeSound(){
        cout <<"Animal Making sound" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound(){
        cout <<"Meow wroom wroom" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound(){
        cout <<" Woof Woof!" << endl;
    }
};

int main() {
    Animal a;
    a.makeSound();
    Cat c;
    c.makeSound();
    Dog d; 
    d.makeSound();

    return 0;
}

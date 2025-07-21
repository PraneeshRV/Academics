#include <iostream>
#include <memory>
using namespace std;
struct A;
struct B;


struct A{
shared_ptr<B> b;
~A() { cout << "~A\n"; }
};

struct B{
weak_ptr<A> a;
~B() { cout << "~B\n"; }
};
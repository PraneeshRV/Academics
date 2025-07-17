//example program for c++ smart pointers
#include<iostream>
#include<memory>

struct A;
struct B;

struct A
{
    std::shared_ptr<B> b;
}

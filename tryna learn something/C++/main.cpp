#include <iostream>
#include <cmath>
using text_t = std::string;

int main(){
    text_t name = "Praneesh";
    std::cout << "Hello " << name << std::endl;
    std::cout<< pow(2,3)<<std::endl;
    std::cout<<sqrt(100)<<std::endl;
    std::cout<<"\a";
    std::cout<<"\n";
    std::cout<<&name;
    
    return 0;
}
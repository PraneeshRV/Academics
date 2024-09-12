//Vector Operations using operator overloading
#include <iostream>
using namespace std;

//vector class
class Vector{

    private:
    int x,y;

    public:

    //default constructor
    Vector(){
        x=0;
        y=0;
    }
    //parameterized constructor
    Vector(int _x,int _y){
        x=_x;
        y=_y;
    }

    //setValue function
    void setValue(int _p,int _q){
        x=_p;
        y=_q;
    }
    //function for printing the vector
    void print(){
        cout<<"("<<x<<","<<y<<")"<<endl;
    }

    //operator overload for vector addition
    Vector operator+(Vector const &other){
        return Vector(x+other.x,y+other.y);
    }
    //operator overload for vector subtraction
    Vector operator-(Vector const &other){
        return Vector(x-other.x,y-other.y);
    }
    //operator overload for vector dot product
    int operator*(Vector const &other){
    return (x*other.x)+(y*other.y);
    }
};
//main function
int main(){

    int a,b,c,d;
//creating the vector objects
    Vector v1;
    v1.setValue(2,4);
    Vector v2(1,2);
    Vector v3;
    Vector v4;
//getting input from user for vectors and using the setValue function to assign them
    cout<<"Enter the values of x and y for vector 1"<<endl;
    cin>>a>>b;
    v3.setValue(a,b);

    cout<<"Enter the values of x and y for vector 2"<<endl;
    cin>>c>>d;
    v4.setValue(c,d);
//sum of 2 vectors
    cout<<"Sum of the vectors"<<endl;
    Vector v5 = v3+v4;
    v5.print();
//subtracting the 2 vectors
    cout<<"Subtraction of the vectors"<<endl;
    Vector v6 = v3-v4;
    v6.print();
//dot product of the 2 vectors
    cout<<"dot product of the vectors"<<endl;
    int dot = v3*v4;
    cout<<dot<<endl;

    return 0;
}

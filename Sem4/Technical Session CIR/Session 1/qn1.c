#include <iostream>
using namespace std;
int main(){
    int no_of_terms;
    cout<<"Enter the number of terms: ";
    cin>>no_of_terms;
    int array[no_of_terms];
    
    for (int i = 1; i <= no_of_terms; i++){
        array[i-1]=i*i;
    }
    for (int i = 0; i < no_of_terms; i++)
    {
        cout <<i<<"*"<<i<<" = "<<array[i]<<endl;
    }
}
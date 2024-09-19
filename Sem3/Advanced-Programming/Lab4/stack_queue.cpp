#include <iostream>
#include <stack>
#include <queue>
using namespace std;
int main(){
    stack<int> myStack;
    queue<int> myQueue;
    myStack.push(10);
    myStack.push(50);
    myStack.push(420);

    cout<<myStack.top()<<endl;
    myStack.pop();
    cout<<myStack.top()<<endl;
    cout<<myStack.size()<<endl;
    if(myStack.empty()){
        cout<<"Stack is empty"<<endl;
    }
    else{
        cout<<"Stack is not empty"<<endl;
    }
    myQueue.push(100);
    myQueue.push(200);
    myQueue.push(690);
    cout<<myQueue.front()<<endl;
    cout<<myQueue.back()<<endl;
    myQueue.pop();
    myQueue.push(1080);
    cout<<myQueue.front()<<endl;
    cout<<myQueue.size()<<endl;
    cout<<"elements in queue are: "<<endl;
    while(!myQueue.empty()){
        cout<<myQueue.front()<<endl;
        myQueue.pop();
}
    return 0;
}
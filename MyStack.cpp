#include "MyStack.h"

using namespace std;

MyStack::MyStack(){

    stackMembers.resize(20);
    for(int i = 0; i<20; i++){
        stackMembers[i] = 0;
    }
    top = -1;
}
bool MyStack::isEmpty(){

    if(top == -1){
        return true;
    }else{
        return false;
    }
}
bool MyStack::isFull(){

    if(top == 19){
        return true;
    }else{
        return false;
    }
}
void MyStack::push(float f){

    if(isFull() == false){
        top++;
        stackMembers[top] = f;
    }
}
float MyStack::pop(){

    if(isEmpty() == false){
        float f = stackMembers[top];
        top--;
        return f;
    }else{
        return 0;
    }
}
void MyStack::printStack(){

    for(int i = 0; i <= top; i++){
        cout << stackMembers[i] << endl;
    }

}




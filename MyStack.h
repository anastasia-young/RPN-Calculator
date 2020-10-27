#ifndef _MYSTACK_H
#define _MYSTACK_H

#include <apstring.h>
#include <apvector.h>


class MyStack{

    private:

        apvector<float> stackMembers;
        int top;

    public:

        MyStack();
        //~MyStack();

        bool isEmpty();
        bool isFull();
        void push(float f);
        float pop();
        void printStack();

};
#endif

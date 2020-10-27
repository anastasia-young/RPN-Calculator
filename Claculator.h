#include "MyStack.h"

class Calculator : public MyStack {

    private:

        float result;

    public:

        Calculator();
        //~Calculator();

        float add();
        float subtract();
        float multiply();
        float divide();
        float display();

};

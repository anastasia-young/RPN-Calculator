#include "Claculator.h"

Calculator::Calculator(){

    MyStack();
    result = 0;

}
float Calculator::add(){

    float f1 = pop();
    float f2 = pop();

    result = f2 + f1;

    push(result);

    return result;

}
float Calculator::subtract(){

    float f1 = pop();
    float f2 = pop();

    result = f2 - f1;

    push(result);

    return result;

}
float Calculator::multiply(){

    float f1 = pop();
    float f2 = pop();

    result = f2 * f1;

    push(result);

    return result;

}
float Calculator::divide(){

    float f1 = pop();
    float f2 = pop();

    result = f2 / f1;

    push(result);

    return result;

}
float Calculator::display(){

    float f1 = pop();
    push(f1);

    return f1;
}


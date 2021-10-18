#include <iostream>
#include <new>
#include "stack.h"

using namespace std;

void Stack::Resize(int n) {
    try {
        int* tmparray = new int[n];
        for (int i = num - 1; i >= 0; i--) {
            tmparray[i] = array[i];
        }
        delete[] array;
        array = tmparray;
    } catch (exception &e) {
        throw StackFull();
    }
}

Stack::Stack(int n) {
    array = new int[n];
    num = n;
    top = -1;
}

Stack::~Stack() {
    delete[] array;
}

void Stack::Push(int n) {
    if (!IsFull()) {
        top++;
        array[top] = n;
    } else {
        Resize(num * 2);
        num *= 2;
        Push(n);
    } 
}

void Stack::Pop() {
    if (IsEmpty()) {
        throw StackEmpty();
    } else {
        top--;
    }
}

bool Stack::IsEmpty() const {
    return (top == -1);
}   

bool Stack::IsFull() const {
    return (top == num - 1);
}

void Stack::MakeEmpty() {
    top = -1;
}

int Stack::Top() const {
    if (!IsEmpty()) {
        return Peek(0);
    } else {
        throw StackEmpty();
    }
}

int Stack::Size() const {
    return top + 1;
}

int Stack::Max() const {
    if (IsEmpty()) {
        throw StackEmpty();
    } else {
        int max = Peek(0);
        for (int i = 0; i <= top; i++) {
            if (Peek(i) > max) {
                max = Peek(i);
            }
        }
        return max;
    }
}

int Stack::Min() const {
    if (IsEmpty()) {
        throw StackEmpty();
    } else {
        int min = Peek(0);
        for (int i = 0; i <= top; i++) {
            if (Peek(i) < min) {
                min = Peek(i);
            }
        }
        return min;
    }
}

int Stack::Peek(unsigned int n) const {
    if (n > top || IsEmpty()) {
        throw StackInvalidPeek();
    } else {
        return array[top - n];
    }
}

int Stack::Capacity() const {
    return num;
}

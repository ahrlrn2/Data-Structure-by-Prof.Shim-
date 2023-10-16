#ifndef _STACK_H_
#define _STACK_H_
#include <cstdio>


template <class T>
class Stack{
    protected:
        int top_index;
        T* stack;
        int capacity;
    public:
        Stack(int capacity = 10);                           //Constructor(default capacity = 10)
        ~Stack();                                           //Destructor
        Stack(const Stack& s);                              //Copy constructor

        int size() const;                                   //stack의 크기 return
        void changeSize(int former_size, int new_size);     //stack의 capacity를 늘릴 때 사용
        bool isEmpty() const;                               //stack이 비었는지 확인
        T& top() const;                                     //stack 가장 위의 element를 return
        void push(const T& element);                        //stack에 element 추가
        void pop();                                         //stack에서 element 제거
};


template <class T>
Stack<T>::Stack(int capacity){
    try{
        if(capacity < 1) throw "Stack capacity must be > 0. Please input appropriate capacity.";        //멤버변수 초기화
        this -> capacity = capacity;
        stack = new T[capacity];
        top_index = -1;
    }
    catch (const char* str){
        printf("%s\n", str);
    }
}

template <class T>
Stack<T>::~Stack(){
    delete[] stack;                     //동적할당한 stack 메모리 할당 해제
}

template <class T>
Stack<T>::Stack(const Stack& s){        
    top_index = s.top_index;            //생성된 stack의 멤버변수를 s의 멤버변수와 동일한 값으로 초기화
    capacity = s.capacity;
    stack = new T[capacity];
    for(int i=0; i <= top_index; i++){
        this -> stack[i] = s.stack[i];  
    }
}

template <class T>
int Stack<T>::size() const {
    return top_index + 1;
}

template <class T>
void Stack<T>::changeSize(int former_size, int new_size){
    try{
        if(new_size < 0) throw "New size is not positive. Please input positive size.";
        int min_size = former_size <= new_size ? former_size : new_size;                   

        T* new_stack = new T[new_size];
        for(int i = 0; i < min_size; i++){
            new_stack[i] = stack[i];                 //former_size와 new_size 중 작은 수만큼 동적 할당된 new_stack에 복사
        }
        delete[] stack;                              //기존에 동적할당되었던 stack 메모리 할당 해제
        stack = new_stack;
        capacity = new_size;                         //stack, capcity 새롭게 assign
    }
    catch (const char* str){
        printf("%s\n", str);
    }
    
}

template <class T>
bool Stack<T>::isEmpty() const{
    return top_index == -1;
}

template <class T>
T& Stack<T>::top() const{
    try{
        if(isEmpty()) throw "Stack is empty";
        return stack[top_index];                   //stack 가장 위의 element
    }
    catch (const char* str){
        printf("%s\n", str);
    }
}

template <class T>
void Stack<T>::push(const T& element){
    if(top_index == capacity - 1)
        changeSize(capacity, 2*capacity);           //stack의 size가 capacity보다 커지게 되면 capacity 2배로 증가
    stack[++top_index] = element;                   //top_index를 1 증가시킴으로써 size 1 증가
}

template <class T>
void Stack<T>::pop(){
    try{
        if(isEmpty()) throw "Stack is empty, Cannot delete.";
        stack[top_index--].~T();                    //top_index를 1 감소시킴으로써 size 1 감소, 가장 위에 있던 element의 destructor 호출함으로써 메모리 할당 해제
    }
    catch (const char* str){
        printf("%s\n", str);
    }
}



#endif
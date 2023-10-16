#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

using std::istream;
using std::ostream;

template <class T>
class CircularList;  // forward declaration

template <class T>
class ChainNode {
    // It contains two fields data and link
public:
    ChainNode() { link = this; }
    ChainNode(const T &e) { data = e; }
    ~ChainNode() {}
    friend class CircularList<T>;
    T GetData() const { return data; }
    ChainNode<T> *GetLink() const { return link; }

private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class CircularList {
public:
    CircularList() { last = new ChainNode<T>; }  // constructor initialize zero polynomial
    // Chain manipulation operations
    void InsertFront(const T &e) {
        // Insert the element e at the "front" of the circular
        // list *this, where last points to the last node in the list.
        ChainNode<T> *newNode = new ChainNode<T>(e);
        if (last) {
            // nonempty list
            newNode->link = last->link;
            last->link = newNode;
        } else {
            // empty list
            last = newNode;
        }
    }
    ChainNode<T> *GetLast() const { return last; }

private:
    ChainNode<T> *last;
};

class Term {
public:
    int coef;  // coefficient
    int exp;   // exponent
    Term() {}
    Term Set(int c, int e) {
        coef = c;
        exp = e;
        return *this;
    };
};

class Polynomial {
public:
    // public functions defined here
    Polynomial();
    Polynomial(const Polynomial &a);                               // (c) Copy constructor
    ~Polynomial();                                                 // (e) Destructor
    Polynomial &operator=(const Polynomial &a);                    // (d) Assign operator
    float Evaluate(float x) const;                                 // (i) Evaluate polynomial
    Polynomial operator+(const Polynomial &b) const;               // (f) Addition
    Polynomial operator-(const Polynomial &b) const;               // (g) Substarction
    Polynomial operator*(const Polynomial &b) const;               // (h) Multiplication
    friend istream &operator>>(istream &is, Polynomial &x);        // (a) Read
    friend ostream &operator<<(ostream &os, const Polynomial &x);  // (b) External representaion

private:
    CircularList<Term> poly;
};

#endif
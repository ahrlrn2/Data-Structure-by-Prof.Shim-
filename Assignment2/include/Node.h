#ifndef NODE_H
#define NODE_H

class Node{
    public:

    int lchild, rchild;
    Node* tail;

    Node(){
        lchild=0;
        rchild=0;
        tail=nullptr;
    }
};

#endif
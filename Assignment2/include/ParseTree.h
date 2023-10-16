#include "Node.h"

class ParseTree{
    public:

    Node* root_node;
    int root_node_index;

    ParseTree(){
        root_node = nullptr;
    }
    ParseTree(Node* node, int root){
        root_node = node;
        root_node_index = root;
    }

    Node& operator[](int index){
        return *(root_node + index);
    }

};
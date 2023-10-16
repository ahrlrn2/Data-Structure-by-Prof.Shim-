#include "Node.h"

class FreeList{
    public:

    Node* root_node;
    Node freelist[31];
    int root_node_index;

    FreeList(){
        root_node = freelist;
        root_node_index = 1;
        for(int i = 0; i < 31; i++){
            if(i<30){
                freelist[i].tail = &freelist[i+1];
            } 
            else{
                freelist[i].tail = &freelist[0];
            }
        }
    }

    Node& operator[](int index){
        return freelist[index];
    }
};
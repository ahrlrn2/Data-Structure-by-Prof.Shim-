#include <iostream>
#include <string>
#include "Node.h"
#include "include/ParseTree.h"
#include "include/HashTable.h"
#include "include/FreeList.h"

void change_to_small(std::string& s){
    for(char& c:s) {
        if (c>='A' && c<='Z') {
            c=c+32;
        }
    }
}


std::string GetNextToken(std::string& s){
    std::string str="";
    int length = s.length();
    int str_len = 0;
    if(length > 0){
        for(char& c: s){
            if(c=='('){
                str = "(";
                s.erase(0,str_len + 1);
                return str;
            }
            else if(c==')'){
                if(str == ""){
                    str = ")";
                    s.erase(0,str_len + 1);
                    return str;
                }
                else{
                    s.erase(0,str_len);
                    return str;
                }
            }
            else if(c==' '){
                if(str != ""){
                    s.erase(0,str_len);
                    return str;
                }
                else{
                    str_len++;
                }
            }
            else{
                str.push_back(c);
                str_len++;
            }
        }
    }
    else{
        return str;
    }
}


int Read(std::string& s, FreeList& freelist, Node* nodearray, HashTable& table){
    int root = 0;
    bool first = true;
    int temp = 0;
    int token_hash_value = table.add_hashvalue(GetNextToken(s));
    if(token_hash_value == table.StringToInt("(")){
        table.add_hashvalue("(");
        table.add_hashvalue(")");
        nodearray[0].lchild = 0;
        nodearray[0].rchild = 0;
        token_hash_value = table.add_hashvalue(GetNextToken(s));
        while(token_hash_value != table.StringToInt(")")){
            if(first){
                freelist.root_node_index++;
                freelist.root_node += 1;
                temp = freelist.root_node_index - 1;
                root = temp;
                first = false;
            }
            else{
                freelist.root_node_index++;
                freelist.root_node += 1;
                temp = freelist.root_node_index - 1;
            }
            if(token_hash_value == table.StringToInt("(")){
                nodearray[temp].lchild = temp + 1;
                s = "(" + s;
                int other_root = Read(s, freelist, nodearray, table);
                nodearray[temp].rchild = freelist.root_node_index;
            } 

            else{
                temp = freelist.root_node_index - 1;
                nodearray[temp].lchild = token_hash_value;
                nodearray[temp].rchild = temp + 1;
            }
            token_hash_value = table.add_hashvalue(GetNextToken(s));
        }
        nodearray[temp].rchild = 0;
        return root;
    }
    else{
        return token_hash_value;
    }
}

void print_root_node_and_tables(FreeList freelist, Node* nodearray, ParseTree tree, HashTable table){
    printf("] Free list's root = ");
    printf("%d\n", freelist.root_node_index);
    printf("Parse tree's root = ");
    printf("%d\n\n\n", tree.root_node_index);
    printf("Node Array =\n");
    for(int i = 0; i < freelist.root_node_index - 1; i++){
        printf("Index: %2d | LeftChild = %8d | RightChild = %8d\n", i + 1, nodearray[i+1].lchild, nodearray[i+1].rchild);
    }
    printf("Hash Table =\n");
    table.print_table();
}

void print_parsetree(ParseTree& tree, HashTable& hashtable, int root, bool startList){
    if(tree.root_node_index == 0){
        printf("()");
    }
    else if(root < 0){
        printf("%s", hashtable.table[hashtable.search_index(root)].symbol.c_str());
    }
    else if(root > 0){
        if(startList){
            printf("(");
        }
        print_parsetree(tree, hashtable, tree[root].lchild, true);
        if(tree[root].rchild != 0){
            printf(" ");
            print_parsetree(tree, hashtable, tree[root].rchild, false);
        }
        else{
            printf(")");
        }
    }
}

void return_memory(FreeList& freelist, ParseTree& tree){
    for(int i=0;i<freelist.root_node_index - 1;i++){
        tree[i].lchild = 0;
        tree[i].rchild = 0;
    }
    freelist.root_node_index = 1;
    freelist.root_node = &freelist[0];
}

int main(){
    FreeList freelist;
    Node* nodearray = freelist.root_node;
    HashTable hash_table;

    while(1){
        char line[1000];
        printf("\n> ");
        gets(line);
        std::string scheme(line);
        change_to_small(scheme);
        int root = Read(scheme, freelist, nodearray, hash_table);
        ParseTree tree(nodearray, root);
        print_root_node_and_tables(freelist, nodearray, tree, hash_table);
        print_parsetree(tree, hash_table, root, true);
        return_memory(freelist, tree);
    }
}
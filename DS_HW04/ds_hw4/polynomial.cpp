#include "polynomial.h"
#include <string>
#include <cmath>


Polynomial::Polynomial(){}

Polynomial::Polynomial(const Polynomial &a){
    Term term;
    ChainNode<Term>* ptr = a.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    int size = 0;
    while(ptr != a.poly.GetLast()){
        size++;
        ptr = ptr -> GetLink();
    }

    if(size != 0){
        Term* term_stack;
        term_stack = new Term[size];
        ptr = ptr -> GetLink();

        for(int i = 0; i < size; i++){
            term_stack[i].Set(ptr->GetData().coef, ptr->GetData().exp);
            ptr = ptr -> GetLink();
        }
        
        for(int i = size - 1; i >= 0; i--){
            poly.InsertFront(term_stack[i]);
        }
        delete[] term_stack;
    }
}                               
Polynomial::~Polynomial(){
    ChainNode<Term>* ptr = poly.GetLast()->GetLink();
    while(ptr != poly.GetLast()){
        ChainNode<Term>* ptr_temp = ptr -> GetLink();
        delete ptr;
        ptr = ptr_temp;
    }
    delete ptr;
}                                     

Polynomial &Polynomial::operator=(const Polynomial &a){
    Term term;
    // ChainNode<Term>* ptr = a.poly.GetLast() -> GetLink();
    // ChainNode<Term>* ptr_this = poly.GetLast() -> GetLink();
    ChainNode<Term>* ptr = a.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    int size = 0;
    while(ptr != a.poly.GetLast()){
        size++;
        ptr = ptr -> GetLink();
    }
    if(size == 0){
        while(ptr_this != poly.GetLast()){
            ChainNode<Term>* ptr_temp = ptr_this -> GetLink();
            delete ptr_this;
            ptr_this = ptr_temp;
        }
        delete ptr_this;
        poly.InsertFront(term);
    }

    else if(size != 0){
        Term* term_stack;
        term_stack = new Term[size];
        ptr = ptr -> GetLink();

        for(int i = 0; i < size; i++){
            term_stack[i].Set(ptr->GetData().coef, ptr->GetData().exp);
            ptr = ptr -> GetLink();
        }

        while(ptr_this != poly.GetLast()){
            ChainNode<Term>* ptr_temp = ptr_this -> GetLink();
            delete ptr_this;
            ptr_this = ptr_temp;
        }
        delete ptr_this;

        CircularList<Term> p;

        for(int i = size - 1; i >= 0; i--){
            p.InsertFront(term_stack[i]);
        }
        poly = p;
        

        delete[] term_stack;
    }
    

    return *this;
}                    

float Polynomial::Evaluate(float x) const{
    float value = 0;
    ChainNode<Term>* ptr = poly.GetLast()->GetLink();
    while(ptr != poly.GetLast()){
        value += ptr->GetData().coef * pow(x, ptr->GetData().exp);
        ptr = ptr -> GetLink();
    }
    return value;
}                                

Polynomial Polynomial::operator+(const Polynomial &b) const{
    Term term;
    Polynomial temp, addRes;
    ChainNode<Term>* ptr = b.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    

    while(1){
        if(ptr_this->GetData().exp == ptr->GetData().exp || (ptr == b.poly.GetLast() && ptr_this == poly.GetLast())){
            if(ptr == b.poly.GetLast())
                break;
            int sum = ptr_this->GetData().coef + ptr->GetData().coef;
            if(sum){
                temp.poly.InsertFront(term.Set(sum, ptr_this->GetData().exp));
            }
            ptr_this = ptr_this -> GetLink();
            ptr = ptr -> GetLink();
        }
        else if(ptr_this->GetData().exp < ptr->GetData().exp || ptr_this == poly.GetLast()){
            temp.poly.InsertFront(term.Set(ptr->GetData().coef, ptr->GetData().exp));
            ptr = ptr -> GetLink();
        }
        else{
            temp.poly.InsertFront(term.Set(ptr_this->GetData().coef, ptr_this->GetData().exp));
            ptr_this = ptr_this -> GetLink();
        }
    }

    ChainNode<Term>* ptr_temp = temp.poly.GetLast()->GetLink();
    while(ptr_temp != temp.poly.GetLast()){
        addRes.poly.InsertFront(term.Set(ptr_temp->GetData().coef, ptr_temp->GetData().exp));
        ptr_temp = ptr_temp -> GetLink();
    }

    return addRes;
}        

Polynomial Polynomial::operator-(const Polynomial &b) const{
    Term term;
    Polynomial temp, diffRes;
    ChainNode<Term>* ptr = b.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    

    while(1){
        if(ptr_this->GetData().exp == ptr->GetData().exp || (ptr == b.poly.GetLast() && ptr_this == poly.GetLast())){
            if(ptr == b.poly.GetLast())
                break;
            int diff = ptr_this->GetData().coef - ptr->GetData().coef;
            if(diff){
                temp.poly.InsertFront(term.Set(diff, ptr_this->GetData().exp));
            }
            ptr_this = ptr_this -> GetLink();
            ptr = ptr -> GetLink();
        }
        else if(ptr_this->GetData().exp < ptr->GetData().exp || ptr_this == poly.GetLast()){
            temp.poly.InsertFront(term.Set(-ptr->GetData().coef, ptr->GetData().exp));
            ptr = ptr -> GetLink();
        }
        else{
            temp.poly.InsertFront(term.Set(ptr_this->GetData().coef, ptr_this->GetData().exp));
            ptr_this = ptr_this -> GetLink();
        }
    }

    ChainNode<Term>* ptr_temp = temp.poly.GetLast()->GetLink();
    while(ptr_temp != temp.poly.GetLast()){
        diffRes.poly.InsertFront(term.Set(ptr_temp->GetData().coef, ptr_temp->GetData().exp));
        ptr_temp = ptr_temp -> GetLink();
    }
    return diffRes;
}      

Polynomial Polynomial::operator*(const Polynomial &b) const{
    Term term;
    Polynomial mulRes;
    ChainNode<Term>* ptr = b.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_mulRes = mulRes.poly.GetLast()->GetLink();


    if(ptr != b.poly.GetLast() && ptr_this != poly.GetLast()){
        while(ptr_this != poly.GetLast()){
            Polynomial temp, reverse_temp;
            ChainNode<Term>* ptr_temp = temp.poly.GetLast();
            ChainNode<Term>* ptr_reverse_temp = reverse_temp.poly.GetLast();

            while(ptr != b.poly.GetLast()){
                temp.poly.InsertFront(term.Set(ptr->GetData().coef * ptr_this->GetData().coef, ptr->GetData().exp + ptr_this->GetData().exp));
                ptr = ptr -> GetLink();
            }

            ptr_temp = ptr_temp -> GetLink();

            while(ptr_temp != temp.poly.GetLast()){
                reverse_temp.poly.InsertFront(term.Set(ptr_temp->GetData().coef, ptr_temp->GetData().exp));
                ptr_temp = ptr_temp -> GetLink();
            }

            mulRes = mulRes + reverse_temp;

            ptr = ptr -> GetLink();
            ptr_this = ptr_this -> GetLink();
        }
    }

    return mulRes;
    
}             

istream &operator>>(istream &is, Polynomial &x){
    std::string input_polynomial;
    is >> input_polynomial;
    std::string token ="";
    Term* term_stack;
    Term term;
    int term_num = 0, coef = 0;
    int size = 0, size_nonzero = 0;
    bool is_term_num = true;
    bool is_coef = true;

    for(char c : input_polynomial){
        if(c == ','){
            if(is_term_num){
                term_num = std::stoi(token);
                if(term_num < 0)
                    std::cerr << "Error: Number of terms is less than 0\n";
                term_stack = new Term[term_num];
                is_term_num = false;
                token.clear();
                continue;
            }
            else{
                if(is_coef){
                    coef = std::stoi(token);
                    is_coef = false;
                }
                else{
                    if(coef != 0){
                        term_stack[size].Set(coef, std::stoi(token));
                        size_nonzero++;
                    }
                    else
                        term_stack[size].Set(coef, 0);
                    if(std::stoi(token) < 0)
                        std::cerr << "Error: exp under 0\n";
                    is_coef = true;
                    size++;
                }
            }
            token.clear();
        }
        else
            token += c;
    }

    if(!token.empty() && !is_term_num){
        if(coef != 0){
            term_stack[size].Set(coef, std::stoi(token));
            size_nonzero++;
        }
        else
            term_stack[size].Set(coef, 0);
        is_coef = true;
        size++;
        if(std::stoi(token) < 0)
            std::cerr << "Error: exp under 0\n";
        if(term_num != size)
            std::cerr << "Error: wrong number of terms\n";
        token.clear();

        for(int i = size - 1; i >= 0; i--){
            if(term_stack[i].coef != 0)
                x.poly.InsertFront(term_stack[i]);
        }
    }
    else if(!token.empty() && is_term_num){
        token.clear();
    }

    if(!is_term_num)
        delete[] term_stack;
    
    term_stack = nullptr;

    return is;
}        
ostream &operator<<(ostream &os, const Polynomial &x){
    ChainNode<Term>* ptr = x.poly.GetLast()->GetLink();
    int size = 0;
    while(ptr != x.poly.GetLast()){
        size++;
        ptr = ptr -> GetLink();
    }

    os << size;

    ptr = ptr -> GetLink();

    while(ptr != x.poly.GetLast()){
        os << ",";
        os << ptr->GetData().coef;
        os << ",";
        os << ptr->GetData().exp;
        ptr = ptr -> GetLink();
    }
    os << "\n";

    return os;
}  
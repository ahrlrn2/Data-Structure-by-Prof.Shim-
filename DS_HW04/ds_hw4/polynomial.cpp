#include "polynomial.h"
#include <string>
#include <cmath>


Polynomial::Polynomial(){}

Polynomial::Polynomial(const Polynomial &a){
    Term term;
    ChainNode<Term>* ptr = a.poly.GetLast()->GetLink();             //last node의 다음 노드로 초기화
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    int size = 0;               
    while(ptr != a.poly.GetLast()){                                 //polynomial a의 term 개수 구하기
        size++;
        ptr = ptr -> GetLink();
    }

    if(size != 0){                                                  //size == 0일 때는 객체 생성만 하면 됨
        Term* term_stack;
        term_stack = new Term[size];                                //term_stack에 메모리 동적 할당
        ptr = ptr -> GetLink();

        for(int i = 0; i < size; i++){                              //stack에 ChainNode를 저장
            term_stack[i].Set(ptr->GetData().coef, ptr->GetData().exp);     
            ptr = ptr -> GetLink();
        }
        
        for(int i = size - 1; i >= 0; i--){
            poly.InsertFront(term_stack[i]);                        //가장 최근에 term_stack에 저장한 element부터 poly에 InsertFront
        }
        delete[] term_stack;                                        //메모리 해제
    }
}                               
Polynomial::~Polynomial(){
    ChainNode<Term>* ptr = poly.GetLast()->GetLink();
    while(ptr != poly.GetLast()){                                   //last node를 제외한 노드 메모리 해제
        ChainNode<Term>* ptr_temp = ptr -> GetLink();
        delete ptr;
        ptr = ptr_temp;
    }
    delete ptr;                                                     //last node 메모리 해제
}                                     

Polynomial &Polynomial::operator=(const Polynomial &a){
    Term term;
    ChainNode<Term>* ptr = a.poly.GetLast()->GetLink();             
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    int size = 0;   
    while(ptr != a.poly.GetLast()){                                 //polynomial a의 term 개수 구하기
        size++;
        ptr = ptr -> GetLink();
    }
    if(size == 0){                                                  //a의 term 개수가 0이면 기존의 ChainNode의 메모리를 해제시키고 새로운 객체를 생성하여 poly에 assign
        while(ptr_this != poly.GetLast()){
            ChainNode<Term>* ptr_temp = ptr_this -> GetLink();
            delete ptr_this;
            ptr_this = ptr_temp;
        }
        delete ptr_this;
        CircularList<Term> p;                                       
        poly = p;
    }

    else if(size != 0){                                             //a의 term 개수가 0이 아니면 기존의 ChainNode의 메모리를 해제시키고 새로운 객체에 stack에 저장한 term들을 insert
        Term* term_stack;
        term_stack = new Term[size];
        ptr = ptr -> GetLink();

        for(int i = 0; i < size; i++){                                          //term_stack에 a의 term 저장
            term_stack[i].Set(ptr->GetData().coef, ptr->GetData().exp);
            ptr = ptr -> GetLink();
        }

        while(ptr_this != poly.GetLast()){                                      //기존의 ChainNode 메모리를 해제
            ChainNode<Term>* ptr_temp = ptr_this -> GetLink();
            delete ptr_this;
            ptr_this = ptr_temp;
        }
        delete ptr_this;

        CircularList<Term> p;   

        for(int i = size - 1; i >= 0; i--){                                     //새로운 객체 term_stack에 저장한 term들을 inserFront
            p.InsertFront(term_stack[i]);
        }
        poly = p;
        

        delete[] term_stack;                                                    //term_stack 메모리 해제
    }
    

    return *this;
}                    

float Polynomial::Evaluate(float x) const{
    float value = 0;
    ChainNode<Term>* ptr = poly.GetLast()->GetLink();
    while(ptr != poly.GetLast()){                                               //last의 link node부터 last node 직전까지 coef * x ^ exp를 계속해서 더하기
        value += ptr->GetData().coef * pow(x, ptr->GetData().exp);
        ptr = ptr -> GetLink();
    }
    return value;
}                                

Polynomial Polynomial::operator+(const Polynomial &b) const{
    Term term;
    Polynomial temp, addRes;                                        //temp: 지수에 대한 오름차순으로 정렬된 polynomial, addRes: 지수에 대한 내림차순으로 정렬된 polynomial(return되는 변수)
    ChainNode<Term>* ptr = b.poly.GetLast()->GetLink();             //ptr: b의 last의 link, ptr_this: this의 last의 link
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    

    while(1){
        if(ptr_this->GetData().exp == ptr->GetData().exp || (ptr == b.poly.GetLast() && ptr_this == poly.GetLast())){       //동류항이거나 ptr, ptr_this가 둘 다 last node를 가리키는 경우
            if(ptr == b.poly.GetLast())                                             //ptr, ptr_this가 둘 다 last node를 가리키는 경우는 연산이 끝난 것이므로 break
                break;
            int sum = ptr_this->GetData().coef + ptr->GetData().coef;               
            if(sum){
                temp.poly.InsertFront(term.Set(sum, ptr_this->GetData().exp));      //sum != 0 일 때만 insert
            }
            ptr_this = ptr_this -> GetLink();
            ptr = ptr -> GetLink();
        }
        else if(ptr_this->GetData().exp < ptr->GetData().exp || ptr_this == poly.GetLast()){            //*ptr_this의 지수가 *ptr의 지수보다 작다면 *ptr의 data를 insert
            temp.poly.InsertFront(term.Set(ptr->GetData().coef, ptr->GetData().exp));
            ptr = ptr -> GetLink();
        }
        else{
            temp.poly.InsertFront(term.Set(ptr_this->GetData().coef, ptr_this->GetData().exp));         //*ptr의 지수가 *ptr_this의 지수보다 작다면 *ptr_this의 data를 insert
            ptr_this = ptr_this -> GetLink();
        }
    }

    ChainNode<Term>* ptr_temp = temp.poly.GetLast()->GetLink();
    while(ptr_temp != temp.poly.GetLast()){                                                             //temp에는 지수에 대한 오름차순으로 정렬되어 있으므로 차례대로 다시 insertFront하여 내림차순으로 정렬
        addRes.poly.InsertFront(term.Set(ptr_temp->GetData().coef, ptr_temp->GetData().exp));          
        ptr_temp = ptr_temp -> GetLink();
    }

    return addRes;
}        

Polynomial Polynomial::operator-(const Polynomial &b) const{                    //덧셈과 logic은 동일
    Term term;
    Polynomial temp, diffRes;
    ChainNode<Term>* ptr = b.poly.GetLast()->GetLink();
    ChainNode<Term>* ptr_this = poly.GetLast()->GetLink();
    

    while(1){
        if(ptr_this->GetData().exp == ptr->GetData().exp || (ptr == b.poly.GetLast() && ptr_this == poly.GetLast())){
            if(ptr == b.poly.GetLast())
                break;
            int diff = ptr_this->GetData().coef - ptr->GetData().coef;          //덧셈과 다르게 coef를 빼줌
            if(diff){
                temp.poly.InsertFront(term.Set(diff, ptr_this->GetData().exp));
            }
            ptr_this = ptr_this -> GetLink();
            ptr = ptr -> GetLink();
        }
        else if(ptr_this->GetData().exp < ptr->GetData().exp || ptr_this == poly.GetLast()){
            temp.poly.InsertFront(term.Set(-ptr->GetData().coef, ptr->GetData().exp));              //*ptr_this의 지수가 *ptr의 지수보다 작다면 *ptr의 data에서 coef의 부호를 바꾸어 insert
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


    if(ptr != b.poly.GetLast() && ptr_this != poly.GetLast()){          //b, this의 term이 존재하지 않는다면 last만 존재하는 mulRes return, 즉 0 return
        while(ptr_this != poly.GetLast()){                          
            Polynomial temp, reverse_temp;                              //temp: 지수에 대한 오름차순으로 정렬된 polynomial, reverse_temp: 지수에 대한 내림차순으로 정렬된 polynomial
            ChainNode<Term>* ptr_temp = temp.poly.GetLast();
            ChainNode<Term>* ptr_reverse_temp = reverse_temp.poly.GetLast();

            while(ptr != b.poly.GetLast()){
                temp.poly.InsertFront(term.Set(ptr->GetData().coef * ptr_this->GetData().coef, ptr->GetData().exp + ptr_this->GetData().exp));      //각 항의 계수끼리 곱하고 지수끼리 더한 결과에 해당하는 data를 temp에 InsertFront
                ptr = ptr -> GetLink();
            }

            ptr_temp = ptr_temp -> GetLink();

            while(ptr_temp != temp.poly.GetLast()){
                reverse_temp.poly.InsertFront(term.Set(ptr_temp->GetData().coef, ptr_temp->GetData().exp));     //temp의 node들을 reverse_temp에 InsertFront함으로써 내림차순으로 정렬
                ptr_temp = ptr_temp -> GetLink();
            }

            mulRes = mulRes + reverse_temp;                             // mulRes에 reverse_temp, 즉 b와 this의 항 1개를 곱한 결과를 더함

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
    int term_num = 0, coef = 0;         //term_num: term 개수, coef: 각 ChainNode의 coef를 저장
    int size = 0, size_nonzero = 0;     
    bool is_term_num = true;            //term 개수에 해당하는 항인지 아닌지 판단
    bool is_coef = true;                //계수인지 아닌지 판단

    for(char c : input_polynomial){
        if(c == ','){                               
            if(is_term_num){                        //term 개수에 해당하는 항이면 term_stack에 메모리를 할당
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
                    coef = std::stoi(token);        //계수 저장
                    is_coef = false;
                }
                else{
                    if(coef != 0){
                        term_stack[size].Set(coef, std::stoi(token));   //지수가 0이 아니면 term_stack에 계수와 지수 저장
                        size_nonzero++;
                    }
                    else
                        term_stack[size].Set(0, -1);                 //지수가 0이 아니면 term_stack에 coef = 0, exp = -1이 되도록 저장
                    if(std::stoi(token) < 0)
                        std::cerr << "Error: exp under 0\n";
                    is_coef = true;
                    size++;
                }
            }
            token.clear();
        }
        else
            token += c;             //','가 없으면 token에 문자 이어붙이기
    }

    if(!token.empty() && !is_term_num){                     //항이 1개 이상인 경우 마지막 항까지 term_stack에 저장
        if(coef != 0){
            term_stack[size].Set(coef, std::stoi(token));
            size_nonzero++;
        }
        else
            term_stack[size].Set(0, -1);
        is_coef = true;
        size++;
        if(std::stoi(token) < 0)
            std::cerr << "Error: exp under 0\n";
        if(term_num != size)
            std::cerr << "Error: wrong number of terms\n";
        token.clear();

        for(int i = size - 1; i >= 0; i--){                 //계수가 0이 아닌 term들만 최근에 저장된 term부터 x.poly에 InsertFront
            if(term_stack[i].coef != 0)
                x.poly.InsertFront(term_stack[i]);
        }
    }
    else if(!token.empty() && is_term_num){                 //항이 0개인 경우 아무 term도 insert하지 않음
        token.clear();
    }

    if(!is_term_num)
        delete[] term_stack;                                //항이 1개 이상인 경우, term_stack 메모리 할당 해제
    
    term_stack = nullptr;

    return is;
}        
ostream &operator<<(ostream &os, const Polynomial &x){
    ChainNode<Term>* ptr = x.poly.GetLast()->GetLink();
    int size = 0;                                           //term의 개수 구하기
    while(ptr != x.poly.GetLast()){
        size++;
        ptr = ptr -> GetLink();
    }

    os << size;                                             //size 출력

    ptr = ptr -> GetLink();

    while(ptr != x.poly.GetLast()){                         //계수와 지수를 차례대로 계속해서 출력
        os << ",";
        os << ptr->GetData().coef;
        os << ",";
        os << ptr->GetData().exp;
        ptr = ptr -> GetLink();
    }
    os << "\n";

    return os;
}  
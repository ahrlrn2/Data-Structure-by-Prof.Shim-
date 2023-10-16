#ifndef _CARD_H_
#define _CARD_H_
#include <cstdio>
#include <string>

enum Shape {diamonds, clubs, hearts, spades};
const std::string denominations[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
class Card{
    private:
    
    Shape shape;            //카드 문양
    std::string denom;      //카드 숫자 또는 알파벳
    int number;             //카드가 나타내는 값(A = 1, 2 = 2, ..., Q = 12, K = 13)
    bool is_front;          //앞면이 보이는지 뒷면이 보이는지를 나타냄

    public:
    Card(Shape shape = diamonds, std::string denom = "A", int number = 1, bool is_front = false);   //Constructor
    Card(const Card& card);                 //copy constructor
    Card& operator=(const Card& card);      //assignment operator

    Shape getShape() const;                 
    std::string getDenom() const;
    int getNumber() const;
    bool getIsFront() const;

    void setIsFront(bool is_front);

    bool isRed() const;                     //빨간색 카드인지 아닌지를 나타냄
    std::string getShapeString() const;     //카드 문양을 string으로 반환
    std::string getAllString() const;       //카드 문양과 숫자 또는 알파벳을 이어붙인 string을 return (Ex. ♦A)
    void print() const;                     //앞면이 보이는지 뒷면이 보이는지를 고려하여 플레이어에게 보이는대로 카드를 print
};

Card::Card(Shape shape, std::string denom, int number, bool is_front){      //멤버변수 초기화
    this -> shape = shape;  
    this -> denom = denom;
    this -> number = number;
    this -> is_front = is_front;
}
Card::Card(const Card& card){       //생성된 객체에 멤버변수 복사
    shape = card.shape;
    denom = card.denom;
    number = card.number;
    is_front = card.is_front;
}
Card& Card::operator=(const Card& card){        //멤버변수 복사
    shape = card.shape;
    denom = card.denom;
    number = card.number;
    is_front = card.is_front;
    return *this;
}

Shape Card::getShape() const{
    return shape;
}
std::string Card::getDenom() const{
    return denom;
}
int Card::getNumber() const{
    return number;
}
bool Card::getIsFront() const{
    return is_front;
}

void Card::setIsFront(bool is_front){
    this -> is_front = is_front;
}

bool Card::isRed() const{
    return (shape == diamonds || shape == hearts);
}

std::string Card::getShapeString() const{
    switch (shape) {
        case diamonds:
            return "\u2666"; 
        case clubs:
            return "\u2663"; 
        case hearts:
            return "\u2665"; 
        case spades:
            return "\u2660"; 
        default:
            return "Unappropriate shape";
    }
}

std::string Card::getAllString() const{
    std::string str = getShapeString();
    str += denom;
    return str;
}

void Card::print() const{
    if(is_front){
        printf("%s", this->getAllString().c_str());         //앞면이 보이는 경우 카드의 문양과 숫자 또는 알파벳을 그대로 출력
    }
    else{
        printf("--");                                       //뒷면이 보이는 경우 -- 출력
    }
}



#endif
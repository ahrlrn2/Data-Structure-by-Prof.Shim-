#ifndef _SOLITAIRE_H_
#define _SOLITAIRE_H_
#include "stack.hpp"
#include "card.hpp"
#include <cstdlib>


typedef Stack<Card> Pile;                                   //편리성을 위해 Pile이라는 이름 사용

class Solitaire{
    private:
    static const int total_cards = 52;                      //총 카드 개수
    static const int output_pile_num = 4;                   //output pile 개수
    static const int playing_pile_num = 7;                  //playing pile 개수
    static const int start_score = -52;                     //최저 점수
    static const int max_score = 208;                       //최대 점수
    int score = -52;                                        //점수(output pile에 카드가 놓여질 때마다 5씩 증가)
    int move_num = 0;                                       //총 이동 횟수
    bool is_end = false;                                    //게임 종료 조건인지 아닌지를 나타냄

    Pile stock;                                             //stock
    Pile waste;                                             //waste pile
    Pile output[output_pile_num];                           //output pile 4개
    Pile playing[playing_pile_num];                         //playing pile 7개


    void initialize(unsigned int random_seed);              //randomly initialize

    bool play2output(Pile& playing_pile, Pile& output_pile, int playing_index, int output_index);       //카드가 특정한 playing pile에서 특정한 output pile로 이동 가능한지 판별 후 가능하다면 이동
    bool waste2output(Pile& waste_pile, Pile& output_pile, int output_index);                           //카드가 waste pile에서 특정한 output_pile로 이동 가능한지 판별 후 가능하다면 이동
    bool waste2play(Pile& waste_pile, Pile& playing_pile, int playing_index);                           //카드가 waste pile에서 특정한 playing pile로 이동 가능한지 판별 후 가능하다면 이동
    bool stock2waste(Pile& stock_pile, Pile& waste_pile);                                               //카드가 stock에서 waste pile로 이동 가능한지 판별 후 가능하다면 이동
    bool play2play(Pile& removed_pile, Pile& gain_pile, int removed_index, int gain_index);             //카드가 특정한 playing pile에서 또다른 특정한 playing pile로 이동 가능한지 판별 후 가능하다면 이동

    bool all_play2output();         //playing pile에서 output pile로 이동 가능한 카드가 있는지 판별 후 가능하다면 이동
    bool all_waste2output();        //waste pile에서 output pile로 이동 가능한 카드가 있는지 판별 후 가능하다면 이동
    bool all_waste2play();          //waste pile에서 playing pile로 이동 가능한 카드가 있는지 판별 후 가능하다면 이동(왼쪽 playing pile 우선)
    bool all_stock2waste();         //stock에서 waste pile로 이동 가능한 카드가 있는지 판별 후 가능하다면 이동
    bool all_play2play();           //playing pile에서 다른 playing pile로 이동 가능한 카드가 있는지 판별 후 가능하다면 이동(왼쪽 playing pile 우선)

    bool sequence_a();              //pdf에 제시된 sequence (a), (b), (c)
    bool sequence_b();
    bool sequence_c();

    void calScore();                //점수 계산

    void print();                   //output 출력
    


    public:
    void play(unsigned int random_seed);        //solitaire play
};

void Solitaire::initialize(unsigned int random_seed){
    Card card[total_cards];
    for(int i = 0; i < 4; i++){                 //52장의 서로 다른 카드 객체 생성
        for(int j = 0; j < 13; j++){
            Shape shape = diamonds;
            switch(i){
                case 0:
                    shape = diamonds;
                    break;
                case 1:
                    shape = clubs;
                    break;
                case 2:
                    shape = hearts;
                    break;
                case 3:
                    shape = spades;
                    break;
            }
            Card c(shape, denominations[j], j + 1, false);
            card[13 * i + j] = c;
        }
    }

    std::srand(random_seed);                        //random seed 적용 후, randomly shuffle
    for(int i = 0; i < total_cards - 1; i++){       //배열의 마지막 카드부터 시작해 random하게 선정된 자신보다 작은 index의 card와 자리 바꿈
        int ind = std::rand() % (total_cards - i);
        Card temp = card[total_cards - 1 - i];      
        card[total_cards - 1 - i] = card[ind];
        card[ind] = temp;
    }

    for(int i = 0; i < total_cards; i++){           //stock에 shuffle된 card를 push
        stock.push(card[i]);
    }
    
    for(int i = 0; i < playing_pile_num; i++){      //playing pile에 차례대로 1~7개의 카드 push 후 맨 위의 카드가 앞면 보이게 설정
        for(int j = 0; j < i + 1; j++){
            playing[i].push(stock.top());
            stock.pop();
            if(j == i)
                playing[i].top().setIsFront(true);
        }
    }
    
}

bool Solitaire::play2output(Pile& playing_pile, Pile& output_pile, int playing_index, int output_index){

    if(playing_pile.isEmpty())                                      //playing_pile이 비어 있다면 이동 불가
        return false;
    else if(output_pile.isEmpty()){                                 //output_pile이 비어 있다면 숫자 부분이 A인 카드만 이동 가능
        if(playing_pile.top().getDenom() == "A"){
            output_pile.push(playing_pile.top());
            playing_pile.pop();
            if(!playing_pile.isEmpty()){                            //이동이 일어나면 playing_pile의 맨 위 카드 앞면 보이게 뒤집기
                if(playing_pile.top().getIsFront() == false)
                    playing_pile.top().setIsFront(true);
            } 
                
            move_num++;
            printf("%d: %s moved from playing pile #%d to output pile #%d\n", move_num, output_pile.top().getAllString().c_str(), playing_index, output_index);
            return true;
        }
        return false;
    }
    else{
        if(playing_pile.top().getShape() == output_pile.top().getShape() && playing_pile.top().getNumber() == output_pile.top().getNumber() + 1){       //나머지 경우, output_pile의 맨 위 카드와 문양이 같고 숫자가 1 더 큰 카드만이 output_pile로 이동 가능
            output_pile.push(playing_pile.top());
            playing_pile.pop();
            if(!playing_pile.isEmpty()){                            //이동이 일어나면 playing_pile의 맨 위 카드 앞면 보이게 뒤집기
                if(playing_pile.top().getIsFront() == false)
                    playing_pile.top().setIsFront(true);
            } 
            move_num++;
            printf("%d: %s moved from playing pile #%d to output pile #%d\n", move_num, output_pile.top().getAllString().c_str(), playing_index, output_index);
            return true;
        }
        return false;
    }
}

bool Solitaire::waste2output(Pile& waste_pile, Pile& output_pile, int output_index){
    if(waste_pile.isEmpty())                                //waste_pile이 비어 있다면 이동 불가
        return false;
    else if(output_pile.isEmpty()){                         //output pile이 비어 있다면 숫자 부분이 A인 카드만 이동 가능
        if(waste_pile.top().getDenom() == "A"){
            output_pile.push(waste_pile.top());
            waste_pile.pop();
            move_num++;
            printf("%d: %s moved from waste pile to output pile #%d\n", move_num, output_pile.top().getAllString().c_str(), output_index);
            return true;
        }
        return false;
    }
    else{
        if(waste_pile.top().getShape() == output_pile.top().getShape() && waste_pile.top().getNumber() == output_pile.top().getNumber() + 1){           //나머지 경우, output_pile의 맨 위 카드와 문양이 같고 숫자가 1 더 큰 카드만이 이동 가능
            output_pile.push(waste_pile.top());
            waste_pile.pop();
            move_num++;
            printf("%d: %s moved from waste pile to output pile #%d\n", move_num, output_pile.top().getAllString().c_str(), output_index);
            return true;
        }
        return false;
    }
}

bool Solitaire::waste2play(Pile& waste_pile, Pile& playing_pile, int playing_index){
    if(waste_pile.isEmpty())                                //waste_pile이 비어 있다면 이동 불가
        return false;
    else if(playing_pile.isEmpty()){                        //playing pile이 비어 있다면 숫자 부분이 K인 카드만 이동 가능
        if(waste_pile.top().getDenom() == "K"){
            playing_pile.push(waste_pile.top());
            waste_pile.pop();
            move_num++;
            printf("%d: %s moved from waste pile to playing pile #%d\n", move_num, playing_pile.top().getAllString().c_str(), playing_index);
            return true;
        }
        return false;
    }
    else{
        if(waste_pile.top().isRed() != playing_pile.top().isRed() && waste_pile.top().getNumber() == playing_pile.top().getNumber() - 1){               //나머지 경우, playing_pile의 맨 위 카드와 색이 다르며 숫자가 1 더 큰 카드만이 이동 가능
            playing_pile.push(waste_pile.top());
            waste_pile.pop();
            move_num++;
            printf("%d: %s moved from waste pile to playing pile #%d\n", move_num, playing_pile.top().getAllString().c_str(), playing_index);
            return true;
        }
        return false;
    }
}

bool Solitaire::stock2waste(Pile& stock_pile, Pile& waste_pile){
    if(stock_pile.isEmpty())                                //stock_pile이 비어 있다면 이동 불가
        return false;
    else{                                                   //나머지 경우, 앞면이 보이게 바꾸고 waste_pile로 이동
        waste_pile.push(stock_pile.top());
        stock_pile.pop();
        waste_pile.top().setIsFront(true);
        move_num++;
        printf("%d: %s moved from stock pile to waste pile\n", move_num, waste_pile.top().getAllString().c_str());
        return true;
    }
}

bool Solitaire::play2play(Pile& removed_pile, Pile& gain_pile, int removed_index, int gain_index){
    Pile temp;                                              //removed_pile에서 앞면이 보이는 카드를 임시적으로 저장할 stack
    if(removed_pile.isEmpty()){                             //removed_pile이 비어 있는 경우 이동 불가
        return false;
    }
    else if(gain_pile.isEmpty()){                           //gain_pile이 비어 있는 경우
        while(removed_pile.top().getIsFront()){             //temp에 removed_pile에서 앞면이 보이는 카드를 임시적으로 저장
            temp.push(removed_pile.top());
            removed_pile.pop();
            if(removed_pile.isEmpty())
                break;
        }
        if(temp.top().getDenom() == "K" && !removed_pile.isEmpty()){        //무한루프 방지를 위해 K 밑에 뒤집혀진 카드가 있는 경우만 이동 가능
            move_num++;
            while(!temp.isEmpty()){
                gain_pile.push(temp.top());
                printf("%d: %s moved from playing pile #%d to playing pile #%d\n", move_num, temp.top().getAllString().c_str(), removed_index, gain_index);
                temp.pop();
            }
            if(!removed_pile.isEmpty()){                                    //removed_pile의 남은 카드 중 맨 위의 카드가 앞면이 보이게 뒤집기
                if(removed_pile.top().getIsFront()==false)
                    removed_pile.top().setIsFront(true);
            }
                
            return true;
        }
        else{
            while(!temp.isEmpty()){                                         //이동 불가한 경우, removed_pile 원상복구
                removed_pile.push(temp.top());
                temp.pop();
            }
            return false;
        }
    }
    else{
        while(removed_pile.top().getIsFront()){                             //temp에 removed_pile에서 앞면이 보이는 카드를 임시적으로 저장
            temp.push(removed_pile.top());
            removed_pile.pop();
            if(removed_pile.isEmpty())
                break;
        }
        if(temp.top().isRed() != gain_pile.top().isRed() && temp.top().getNumber() == gain_pile.top().getNumber() - 1){         //나머지 경우, temp의 맨 위 즉, removed_pile에서 앞면이 보이는 가장 밑의 카드가 gain_pile의 맨 위 카드와 색이 다르고 숫자가 gain_pile의 맨 위 카드보다 1 적을 때만 이동 가능
            move_num++;
            while(!temp.isEmpty()){
                gain_pile.push(temp.top());
                printf("%d: %s moved from playing pile #%d to playing pile #%d\n", move_num, temp.top().getAllString().c_str(), removed_index, gain_index);
                temp.pop();
            }
            if(!removed_pile.isEmpty()){                                    //removed_pile의 남은 카드 중 맨 위의 카드가 앞면이 보이게 뒤집기
                if(removed_pile.top().getIsFront()==false)
                    removed_pile.top().setIsFront(true);
            }
            
            return true;
        }
        else{
            while(!temp.isEmpty()){                                         //이동 불가한 경우, removed_pile 원상복구
                removed_pile.push(temp.top());
                temp.pop();
            }
            return false;
        }
    }
}

bool Solitaire::all_play2output(){
    bool can_move = false;
    for(int i = 0; i < playing_pile_num; i++){                              //모든 playing pile과 output pile에 대해 playing pile에서 output pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 카드 이동
        for(int j = 0; j < output_pile_num; j++){
            if(play2output(playing[i], output[j], i + 1, j + 1)){
                can_move = true;
                break;
            }
        }
        if(can_move)
            break;
    }
    return can_move;
}

bool Solitaire::all_waste2output(){
    bool can_move = false;
    for(int i = 0; i < output_pile_num; i++){                               //waste pile과 모든 output pile에 대해 waste pile에서 output pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 카드 이동
        if(waste2output(waste, output[i], i + 1)){
            can_move = true;
            break;
        }
    }
    return can_move;
}

bool Solitaire::all_waste2play(){
    bool can_move = false;
    for(int i = 0; i < playing_pile_num; i++){                              //waste pile과 모든 playing pile에 대해 waste pile에서 playing pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 카드 이동(왼쪽 playing pile 우선)
        if(waste2play(waste, playing[i], i + 1)){
            can_move = true;
            break;
        }
    }
    return can_move;
}

bool Solitaire::all_stock2waste(){
    return stock2waste(stock, waste);                                       //stock에서 waste pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 이동
}

bool Solitaire::all_play2play(){
    bool can_move = false;
    for(int i = 0; i < playing_pile_num; i++){                              //모든 playing pile에 대해 다른 playing pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 이동(왼쪽 playing pile 우선)
        for(int j = 0; j < playing_pile_num; j++){
            if(j == i)
                continue;
            if(play2play(playing[i], playing[j], i + 1, j + 1)){
                can_move = true;
                break;
            }
        }
        if(can_move)
            break;
    }
    return can_move;
}

bool Solitaire::sequence_a(){                           //playing pile과 waste pile에서 output pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 이동
    if(all_play2output())
        return true;
    else if(all_waste2output())
        return true;
    else
        return false;
}

bool Solitaire::sequence_b(){                           //waste pile이 비었으면 stock에서 waste pile로 카드 이동, 나머지 경우는 waste pile에서 playing pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 이동
    if(waste.isEmpty())
        return all_stock2waste();
    else
        return all_waste2play();
}

bool Solitaire::sequence_c(){                           //모든 playing pile에 대해 다른 playing pile로 이동할 수 있는 카드가 있는지 판단, 가능하다면 이동(왼쪽 playing pile 우선)
    return all_play2play();
}

void Solitaire::calScore(){                             //output pile의 카드 개수에 따라 점수 계산
    int output_card_num = 0;
    for(int i=0; i < output_pile_num; i++){
        output_card_num += output[i].size();
    }
    score = start_score + 5 * output_card_num;
}

void Solitaire::print(){
    printf("Score: %d\n", score);
    printf("Piles:\n");
    printf("Stock     Waste          Output1     Output2     Output3     Output4\n");

    if(stock.isEmpty())
        printf("empty     ");
    else{
        printf(" ");
        stock.top().print();
        printf("       ");
    }

    if(waste.isEmpty())
        printf("empty          ");
    else{
        printf(" ");
        waste.top().print();
        if(waste.top().getNumber()==10)
            printf("           ");
        else
            printf("            ");
    }

    for(int i = 0; i < output_pile_num; i++){
        if(output[i].isEmpty())
            printf("empty       ");
        else{
            printf("  ");
            output[i].top().print();
            if(output[i].top().getNumber()==10)
                printf("       ");
            else
                printf("        ");;
        }
    }
    printf("\n\n");
    printf("Playing1     Playing2     Playing3     Playing4     Playing5     Playing6     Playing7\n");

    int max_playing_size = 0;
    for(int i = 0; i < playing_pile_num; i++){
        if(playing[i].size() > max_playing_size)
            max_playing_size = playing[i].size();
    }

    Card game_board[max_playing_size][playing_pile_num];            //playing pile을 출력하기 위해 2d array 선언 후, card 객체들을 대입
    for(int i = 0; i < playing_pile_num; i++){
        Pile temp;
        int pile_size = playing[i].size();
        while(!playing[i].isEmpty()){
            temp.push(playing[i].top());
            playing[i].pop();
        }
        for(int j = 0; j < max_playing_size; j++){
            if(j < pile_size){
                game_board[j][i] = temp.top();
                playing[i].push(temp.top());
                temp.pop();
            }
            else{
                Card c(diamonds, "empty", 0, false);
                game_board[j][i] = c;
            }
        }
    }
    
    for(int i = 0; i < max_playing_size; i++){                      //2d array의 객체 차례대로 출력
        for(int j = 0; j < playing_pile_num; j++){
            if(game_board[i][j].getNumber()==0)
                printf("             ");
            else{
                printf("   ");
                game_board[i][j].print();
                if(game_board[i][j].getNumber()==10 && game_board[i][j].getIsFront() == true)
                    printf("       ");
                else
                    printf("        ");
            }
        }
        printf("\n");
    }

    printf("\n---------------------------------------------------------------------------------------------\n");
}

void Solitaire::play(unsigned int random_seed){
    initialize(random_seed);
    printf("Let's start a game!! Random seed is %u\n\n", random_seed);
    while(!is_end){                                  
        calScore();
        print();
        if(sequence_a())
            continue;
        else if(sequence_b())
            continue;
        else if(sequence_c())
            continue;
        else{
            if(!all_stock2waste())                  //stock이 비고 이동이 불가하거나 점수가 최대 점수가 되면 게임 종료
                is_end = true;
            else if(score == max_score)
                is_end = true;
        }
    }
    calScore();
    printf("Final Status\n");
    print();
    printf("Game End!! Your final score is %d\n\n\n", score);
    printf("\n---------------------------------------------------------------------------------------------\n");
}
#endif
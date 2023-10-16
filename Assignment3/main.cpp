#include "solitaire.hpp"

int main(){
    const char* file_name = "output.txt";                       //output.txt에 print한 내용 저장
    freopen(file_name, "w", stdout);
    unsigned int seeds[2] = {0, 1};
    for(int i = 0; i < sizeof(seeds)/sizeof(*seeds); i++){      //주어진 random seed에 대해 게임을 시행
        Solitaire solitaire;
        solitaire.play(seeds[i]);
    }
    fclose(stdout);
}
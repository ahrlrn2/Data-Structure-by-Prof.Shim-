#include <string>

class Hash{
    public:

    int hash_value;
    std::string symbol;
    int link_of_value;
};

class HashTable{
    public:
    Hash table[31];

    HashTable(){
        for(int i=0;i<31;i++){
            setHashValues(i, 0, "", 0);
        }
        
    }

    void setHashValues(int index, int hash_value, std::string symbol, int link_of_value){
        table[index].hash_value = hash_value;
        table[index].symbol = symbol;
        table[index].link_of_value = link_of_value;
    }

    Hash getHashValue(int index){
        return table[index];
    }

    int search_index(int hash_value){
        for(int i = 0; i < 31; i++){
            if(table[i].hash_value == hash_value){
                return i;
                break;
            }
        }
        return -1;
    }

    int StringToInt(std::string s){
        int length = (int)s.length();
        int answer = 0;

        if(length%2==1){
            answer = s.at(length-1);
            length--;
        }
        for(int i=0; i<length; i+=2){
            answer += s.at(i);
            answer += ((int)s.at(i+1)) << 8;
        }

        return -answer;
    }

    bool is_full(){
        for(int i = 0; i < 31; i++){
            if(table[i].hash_value == 0){
                return false;
            }
        }
        return true;
    }

    int add_hashvalue(std::string s){
        int val = StringToInt(s);
        if(search_index(val) >= 0){
            return val;
        }
        int res_val = (-val)%30 + 1;
        while(!is_full()){
            if(table[res_val].hash_value == 0){
                setHashValues(res_val,val,s,0);
                break;
            }
            else{
                res_val++;
                if(res_val > 30){
                    res_val -= 30;
                } 
            }
        }
        return val;
    }

    void print_table(){
        for(int i = 0; i < 31; i++){
            if(table[i].hash_value != 0){
                printf("Hash Value: %8d | Symbol = %10s | Link of Value = %2d\n", table[i].hash_value, table[i].symbol.c_str(), table[i].link_of_value);
            }
        }
    }

};
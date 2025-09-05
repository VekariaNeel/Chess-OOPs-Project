#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Player{
private:
    string name;
    bool isWhite;

public:
    Player(string n, bool isWhite){
        name = n;
        isWhite=isWhite;
    }

    string getname(){return name;}
    bool iswhiteside(){return isWhite;}

};

int main(){
    return 0;
}
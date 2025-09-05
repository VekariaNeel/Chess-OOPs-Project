#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Player{
private:
    string name;
    bool iswhite;

public:
    Player(string n, bool isWhite){
        name = n;
        iswhite=isWhite;
    }

    string getname(){return name;}
    bool iswhiteside(){return iswhite;}

};

int main(){
    return 0;
}
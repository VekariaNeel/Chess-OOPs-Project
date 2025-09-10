#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void invalid()
{
    cout<<"INVALID MOVE PLZ TRY AGAIN\n";
}


void success()
{
    cout<<"MOVE COMPLETED\n";
}


class rook{
private:
    int x,y;
public:
    rook(int a,int b)
    {
        x=a;
        y=b;
    }
    bool move(int a,int b)
    {
        if((a==x && b!=y) || (a!=x && b==y))
        {
            x=a;
            y=b;
            success();
            return true;
        }
        else{
            invalid();
            return false;
        }
    }
};

class Player{
private:
    string name;
    bool isWhite;

public:


    Player(string n, bool isw){
        name = n;
        isWhite=isw;
    }

    string getname(){return name;}
    bool iswhiteside(){return isWhite;}

};


int main(){
    return 0;
}
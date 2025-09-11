#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void invalid()
{
    cout << "INVALID MOVE PLZ TRY AGAIN\n";
}

void success()
{
    cout << "MOVE COMPLETED\n";
}

class pieces{
    protected:
    string name,color;
    public:
    pieces(string na,string col){
        color=col;
        name=na; 
    }
    pieces(){
        name='.';
    }
    virtual bool isvalid(int sti,int stj, int endi, int endj ,string col) =0;
}; 
class rook : public pieces
{
public:
    rook(string col) : pieces("ROOK",col){};
    bool isvalid(int sti,int stj, int endi, int endj ,string col){

    }
};
class bishop{
    private:
        int x,y;
    public:
        bishop(int a,int b){
            x=a;
            y=b;
        }
        
        bool move(int a,int b){
            if(abs(a-x)==abs(b-y) && a<=8 && a>=0 && b<=8 && b>=0){
                // isvalidMove();
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
class pawn
{
    int x, y;

public:
    pawn(int a, int b)
    {
        x = a;
        y = b;
    }

    // bool checkKill()
    // {

    // }


    bool move(int a, int b)
    {
        if (y == 1)
        {
            if (a == x and (b == y + 1 or b == y + 2))
            {
                x = a;
                y = b;
                success();
                return true;
            }
        }
        else if (a == x and b == y + 1)
        {
            x = a;
            y = b;
            success();
            return true;
        }
        invalid();
        return false;
    }
};

class Board
{
private:
    vector<vector<pieces*>> grid;
public:
    Board()
    {
        grid.resize(8, vector<pieces*>(8,NULL));
    }
    void display(){
        cout << "   1  2  3  4  5  6  7  8\n";
        cout << "  -------------------------\n";
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
                cout << " " << grid[r][c] << " ";
            }
            cout << "| " << (8 - r) << "\n";
        }
        cout << "  -------------------------\n";
        cout << "   1  2  3  4  5  6  7  8\n";
    }
};
class Player
{
private:
    string name;
    bool isWhite;

public:
    Player(string n, bool isw)
    {
        name = n;
        isWhite = isw;
    }

    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
};

int main()
{
    Player p1("Shubham", false);
    Player p2("Neel", true);

    cout << p1.getname() << " " << (p1.iswhiteside() ? "is white" : "is black") << endl;
    cout << p2.getname() << " " << (p2.iswhiteside() ? "is white" : "is black") << endl;

    Board board;
    board.display();

    cout<<"Game Start"<<endl<<endl;
    
    return 0;
}
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

void invalid()
{
    cout << "INVALID MOVE PLZ TRY AGAIN\n";
}

void success()
{
    cout << "MOVE COMPLETED\n";
}

class pieces
{
protected:
    string name, color;

public:
    pieces(string na, string col)
    {
        color = col;
        name = na;
    }
    pieces()
    {
        name = '.';
    }
    virtual bool isvalid(int sti, int stj, int endi, int endj, string col) = 0;
};
class rook : public pieces
{
public:
    rook(string col) : pieces("ROOK", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, string col)
    {
    }
};
class bishop
{
private:
    int x, y;

public:
    bishop(int a, int b)
    {
        x = a;
        y = b;
    }

    bool move(int a, int b)
    {
        if (abs(a - x) == abs(b - y) && a <= 8 && a >= 0 && b <= 8 && b >= 0)
        {
            // isvalidMove();
            x = a;
            y = b;
            success();
            return true;
        }
        else
        {
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
    pieces* grid[8][8];

public:
    // Board()
    // {
    //     vector<vector<piece>> chessBoard(8, vector<piece>(8));

    //     grid.resize(8, vector<char>(8, '.'));
    // }
    void display()
    {
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
    int timeleft;

public:
    Player(string n, bool isw, int t=30)
    {
        name = n;
        isWhite = isw;
        timeleft = t;
    }

    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
    int gettime(){return timeleft;}

     void countdown() {
        while (timeleft > 0) {
            cout << "\r" << name << " time left: " << timeleft << " sec   " << flush;
            this_thread::sleep_for(chrono::seconds(1));
            timeleft--;
        }
        cout << "\n" << name << " ran out of time!\n";
    }
};

int main()
{
    Player p1("Shubham", false, 30);
    Player p2("Neel", true, 30);

    Board grid[8][8];

    cout << p1.getname() << " " << (p1.iswhiteside() ? "is white" : "is black") << endl;
    cout << p2.getname() << " " << (p2.iswhiteside() ? "is white" : "is black") << endl;
    Board board;
    board.display();

    cout << "Game Start" << endl
         << endl;

    p1.countdown();
    return 0;
}
#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void invalid()
{
    cout << "INVALID MOVE PLZ TRY AGAIN\n";
    cout << "INVALID MOVE PLZ TRY AGAIN\n";
}

void success()
{
    cout << "MOVE COMPLETED\n";
    cout << "MOVE COMPLETED\n";
}

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

class rook
{
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

class rook
{
private:
    int x, y;

    int x, y;

public:
    rook(int a, int b)
    rook(int a, int b)
    {
        x = a;
        y = b;
        x = a;
        y = b;
    }
    bool move(int a, int b)
    bool move(int a, int b)
    {
        if ((a == x && b != y) || (a != x && b == y))
        if ((a == x && b != y) || (a != x && b == y))
        {
            x = a;
            y = b;
            x = a;
            y = b;
            success();
            return true;
        }
        else
        {
        else
        {
            invalid();
            return false;
        }
    }
};


class Board

{
private:
    vector<vector<char>> grid;


public:
    Board()
    {
        grid.resize(8, vector<char>(8, '.'));
    }
    void display()
    
    {
        cout << "   a  b  c  d  e  f  g  h\n";
        cout << "  -------------------------\n";
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
                cout << " " << grid[r][c] << " ";
            }
            cout << "| " << (8 - r) << "\n";
            cout << "| " << (8 - r) << "\n";
        }
        cout << "  -------------------------\n";
        cout << "   a  b  c  d  e  f  g  h\n";
    }
};
class Player
{
class Player
{
private:
    string name;
    bool isWhite;

public:
    Player(string n, bool isw)
    {
    Player(string n, bool isw)
    {
        name = n;
        isWhite = isw;
        isWhite = isw;
    }

    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
};

int main()
{
int main()
{
    Player p1("Shubham", false);
    Player p2("Neel", true);

    cout << p1.getname() << " " << (p1.iswhiteside() ? "is white" : "is black") << endl;
    cout << p2.getname() << " " << (p2.iswhiteside() ? "is white" : "is black") << endl;

    Board board;
    board.display();
    return 0;
}
#include <iostream>

using namespace std;

class pieces
{
protected:
    string name;
    bool iswhite;

public:
    pieces(string na, bool col)
    {
        iswhite = col;
        name = na;
    }
    virtual bool isvalid(int sti, int stj, int endi, int endj, bool col, pieces ***grid) const = 0;
    bool isWhite() const { return iswhite; }
};
class rook : public pieces
{
public:
    rook(bool col) : pieces("ROOK", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if ((sti == endi && stj != endj))
        {
            int ad = -1;
            if (endj > stj)
                ad = 1;
            for (int i = stj + ad; stj == endj; i += ad)
            {
                if (grid[sti][i] == nullptr || stj == endj)
                    continue;
                // if(grid[sti][i]->isWhite() == grid[sti][stj]->isWhite()) return false;
                // if(stj!=endj) return false;
                return false;
            }
            return true;
        }
        else if ((sti != endi && stj == endj))
        {
            int ad = -1;
            if (endi > sti)
                ad = 1;
            for (int i = sti + ad; sti == endi; i += ad)
            {
                if (grid[i][stj] == nullptr || sti == endi)
                    continue;
                // if(grid[sti][i]->isWhite() == grid[sti][stj]->isWhite()) return false;
                // if(stj!=endj) return false;
                return false;
            }
            return true;
        }
        return false;
    }
};
class knight : public pieces
{
public:
    knight(bool col) : pieces("KNIGHT", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override {}
};
class queen : public pieces
{
public:
    queen(bool col) : pieces("QUEEN", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override {}
};
class king : public pieces
{
public:
    king(bool col) : pieces("KING", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override {}
};
class bishop : public pieces
{
private:
    int x, y;

public:
    bishop(bool col) : pieces("BISHOP", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override {}
    bool move(int a, int b)
    {
        if (abs(a - x) == abs(b - y) && a <= 8 && a >= 0 && b <= 8 && b >= 0)
        {
            // isvalidMove();
            x = a;
            y = b;
            // success();
            return true;
        }
        else
        {
            // invalid();
            return false;
        }
    }
};
class pawn : public pieces
{
    int x, y;

public:
    pawn(bool col) : pieces("PAWN", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override {}
    bool move(int a, int b)
    {
        if (y == 1)
        {
            if (a == x and (b == y + 1 or b == y + 2))
            {
                x = a;
                y = b;
                // success();
                return true;
            }
        }
        else if (a == x and b == y + 1)
        {
            x = a;
            y = b;
            // success();
            return true;
        }
        // invalid();
        return false;
    }
};

class Board
{
private:
    pieces ***grid;
    friend class pieces;

public:
    Board()
    {
        grid = (pieces ***)malloc(8 * sizeof(pieces **));
        for (int i = 0; i < 8; i++)
        {
            grid[i] = (pieces **)malloc(8 * sizeof(pieces *));
            for (int j = 0; j < 8; j++)
            {
                if (i == 1)
                    grid[i][j] = new pawn(false);
                else if (i == 6)
                    grid[i][j] = new pawn(true);
                else
                    grid[i][j] = nullptr;
            }
        }
        initboard();
    }

    void initboard()
    {
        grid[0][0] = new rook(false);
        grid[0][1] = new knight(false);
        grid[0][2] = new bishop(false);
        grid[0][3] = new queen(false);
        grid[0][4] = new king(false);
        grid[0][5] = new bishop(false);
        grid[0][6] = new knight(false);
        grid[0][7] = new rook(false);

        grid[7][0] = new rook(true);
        grid[7][1] = new knight(true);
        grid[7][2] = new bishop(true);
        grid[7][3] = new queen(true);
        grid[7][4] = new king(true);
        grid[7][5] = new bishop(true);
        grid[7][6] = new knight(true);
        grid[7][7] = new rook(true);
    }
    void display()
    {
        cout << "   1  2  3  4  5  6  7  8\n";
        cout << "  -------------------------\n";
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
                if (grid[r][c] == nullptr)
                    cout << " . ";
                else
                    cout << " P ";
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
    Player(string n, bool isw, int t = 30)
    {
        name = n;
        isWhite = isw;
        timeleft = t;
    }

    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
    int gettime() { return timeleft; }

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
         
    return 0;
}
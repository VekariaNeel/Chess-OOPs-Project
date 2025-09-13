#include <iostream>

using namespace std;

class pieces
{
protected:
    bool iswhite;

public:
    string name;
    pieces(string na, bool col)
    {
        iswhite = col;
        name = na;
    }
    virtual bool isvalid(int sti, int stj, int endi, int endj, bool col, pieces ***grid) const = 0;
    // virtual bool move(int sti, int stj, int endi, int endj,pieces ***grid) const = 0;
    bool isWhite() const { return iswhite; }
};
class rook : public pieces
{
public:
    rook(bool col) : pieces("ROOK", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (sti < 0 || sti > 7 || stj < 0 || stj > 7 || endi < 0 || endi > 7 || endj < 0 || endj > 7)
            return false;
        if (sti == endi && stj == endj)
            return false;
        if (sti == endi)
        {
            int step = (endj > stj) ? 1 : -1;
            for (int j = stj + step; j != endj; j += step)
            {
                if (grid[sti][j] != nullptr) // rasta ma vache koi avi jay to
                    return false;
            }
            if (grid[endi][endj] == nullptr)
                return true;
            return (grid[endi][endj]->isWhite() != iswhite);
        }

        else if (stj == endj)
        {
            int step = (endi > sti) ? 1 : -1;
            for (int i = sti + step; i != endi; i += step)
            {
                if (grid[i][stj] != nullptr)
                    return false;
            }
            if (grid[endi][endj] == nullptr)
                return true;
            return (grid[endi][endj]->isWhite() != iswhite);
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
public:
    bishop(bool col) : pieces("BISHOP", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (abs(endi - sti) == abs(endj - stj) && endi <= 8 && endi >= 0 && endj <= 8 && endj >= 0 && endi != sti && endj != stj)
        {
            if (grid[endi][endj]->isWhite() == iswhite)
                return false;
            int adi = -1;
            int adj = -1;
            if (sti < endi)
                adi = 1;
            if (stj < endj)
                adj = 1;
            int i = sti + adi;
            int j = stj + adj;
            while (sti < endi)
            {
                if (grid[i][j] != nullptr)
                    return false;
                i += adi;
                j += adj;
            }
            return true;
        }
        return false;
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

    void move(string st, string end)
    {
        int stj = st[0] - 'a';      
        int sti = 8 - (st[1] - '0');  
        int endj = end[0] - 'a';
        int endi = 8 - (end[1] - '0');

        if(grid[sti][stj] == nullptr){
            cout << "No piece at starting square!\n";
            return;
        }

        if(grid[sti][stj]->isvalid(sti, stj, endi, endj, grid[sti][stj]->isWhite(), grid))
        {
            if(grid[endi][endj] != nullptr){
                if (grid[endi][endj]->isWhite() == grid[sti][stj]->isWhite()){
                    cout << "Cannot capture your own piece!\n";
                    return;
                }
                delete grid[endi][endj];
            }
            grid[endi][endj] = grid[sti][stj];
            grid[sti][stj] = nullptr;
        }
        else
        {
            cout << "INVALID MOVE\n";
        }
    }
    void display()
    {
        cout << "    a  b  c  d  e  f  g  h\n";
        cout << "  -------------------------\n";
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
                if (grid[r][c] == nullptr)
                    cout << " . ";
                else
                {
                    if (grid[r][c]->isWhite())
                        cout << " W";
                    else
                        cout << " B";
                    cout << grid[r][c]->name[0];
                }
            }
            cout << " | " << (8 - r) << "\n";
        }
        cout << "  -------------------------\n";
        cout << "    a  b  c  d  e  f  g  h\n";
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

    // Board grid[8][8];

    cout << p1.getname() << " " << (p1.iswhiteside() ? "is white" : "is black") << endl;
    cout << p2.getname() << " " << (p2.iswhiteside() ? "is white" : "is black") << endl;
    Board board;
    board.display();
    cout << "Game Start" << endl
         << endl;
    while (1)
    {
        string in1, in2;
        cout << "enter starting pos :";
        getline(cin, in1);
        cout << "enter ending pos :";
        getline(cin, in2);
        board.move(in1, in2);
        board.display();
    }
    return 0;
}
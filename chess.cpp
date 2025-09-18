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
    bool isWhite() const { return iswhite; }
};
class rook : public pieces
{
public:
    rook(bool col) : pieces("ROOK", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (sti == endi)
        {
            int step = (endj > stj) ? 1 : -1;
            for (int j = stj + step; j != endj; j += step)
            {
                if (grid[sti][j] != nullptr)
                    return false;
            }
            return true;
        }
        else if (stj == endj)
        {
            int step = (endi > sti) ? 1 : -1;
            for (int i = sti + step; i != endi; i += step)
            {
                if (grid[i][stj] != nullptr)
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
    knight(bool col) : pieces("NIGHT", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if ((abs(sti - endi) == 2 && abs(stj - endj) == 1) || (abs(sti - endi) == 1 && abs(stj - endj) == 2))
            return true;
        return false;
    }
};
class queen : public pieces
{
public:
    queen(bool col) : pieces("QUEEN", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (sti == endi)
        {
            int step = (endj > stj) ? 1 : -1;
            for (int j = stj + step; j != endj; j += step)
            {
                if (grid[sti][j] != nullptr)
                    return false;
            }
            return true;
        }
        else if (stj == endj)
        {
            int step = (endi > sti) ? 1 : -1;
            for (int i = sti + step; i != endi; i += step)
            {
                if (grid[i][stj] != nullptr)
                    return false;
            }
            return true;
        }
        if (abs(sti - endi) != abs(stj - endj))
            return false;
        int adi = -1;
        int adj = -1;
        if (sti < endi)
            adi = 1;
        if (stj < endj)
            adj = 1;
        int i = sti + adi;
        int j = stj + adj;
        while (i != endi)
        {
            if (grid[i][j] != nullptr)
                return false;
            i += adi;
            j += adj;
        }
        return true;
    }
};
class king : public pieces
{
public:
    king(bool col) : pieces("KING", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        int dx = abs(sti - endi);
        int dy = abs(stj - endj);

        if ((dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0))
            return true;
        return false;
    }
};

class bishop : public pieces
{
public:
    bishop(bool col) : pieces("BISHOP", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (abs(sti - endi) != abs(stj - endj))
            return false;
        int adi = -1;
        int adj = -1;
        if (sti < endi)
            adi = 1;
        if (stj < endj)
            adj = 1;
        int i = sti + adi;
        int j = stj + adj;

        while (i != endi)
        {
            if (grid[i][j] != nullptr)
                return false;
            i += adi;
            j += adj;
        }
        return true;
        return true;
    }
};

class pawn : public pieces
{
public:
    pawn(bool col) : pieces("PAWN", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (endj == stj)
        {
            if (!isWhite())
            {
                if (sti == 1)
                {
                    if ((endi == sti + 2 and grid[sti + 2][endj] == nullptr and grid[sti + 1][endj] == nullptr) or (endi == sti + 1 and grid[sti + 1][endj] == nullptr))
                    return true;
                }
                else if (endi == sti + 1)
                return true;
            }
            else
            {
                if (sti == 6)
                {
                    if ((endi == sti - 2 and grid[sti - 2][endj] == nullptr and grid[sti - 1][endj] == nullptr) or (endi == sti - 1 and grid[sti - 1][endj] == nullptr))
                        return true;
                }
                else if (endi == sti - 1 and grid[sti - 1][endj] == nullptr)
                    return true;
            }
        }

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

    bool king_in_check(bool white)
    {
        int kingi = -1, kingj;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (grid[i][j] != nullptr && grid[i][j]->name == "KING" && grid[i][j]->isWhite() == white)
                {
                    kingi = i;
                    kingj = j;
                    break;
                }
            }
            if (kingi != -1)
                break;
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (grid[i][j] != nullptr && grid[i][j]->isWhite() != white)
                {
                    if (grid[i][j]->isvalid(i, j, kingi, kingj, grid[i][j]->isWhite(), grid))
                        return true;
                }
            }
        }
        return false;
    }
    bool move(string st, string end, bool whiteTurn)
    {
        int stj = st[0] - 'a', sti = 8 - (st[1] - '0'), endj = end[0] - 'a', endi = 8 - (end[1] - '0');
        if (grid[sti][stj]->isWhite() != whiteTurn)
        {
            cout << "INVALID MOVE" << endl;
            cout << "It's not your piece" << endl;
            return false;
        }
        if (sti < 0 || sti > 7 || stj < 0 || stj > 7 || endi < 0 || endi > 7 || endj < 0 || endj > 7 || (sti == endi && stj == endj))
        {
            cout << "INVALID MOVE\n";
            return false;
        }
        else if (grid[sti][stj] == nullptr)
        {
            cout << "No piece at starting square!\n";
            return false;
        }
        if (grid[sti][stj]->isvalid(sti, stj, endi, endj, grid[sti][stj]->isWhite(), grid))
        {
            if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == grid[sti][stj]->isWhite())
            {
                cout << "Cannot capture your own piece!\n";
                return false;
            }
            pieces *end = grid[endi][endj];
            grid[endi][endj] = grid[sti][stj];
            grid[sti][stj] = nullptr;
            // if(king_in_check(grid[sti][stj]->isWhite())){
            //         cout<<"INVALID MOVE YOUR KING WOULD BE IN CHECK";
            //         grid[sti][stj]=grid[endi][endj];
            //         grid[endi][endj]=end;
            //         return false;
            //     }

            cout << "helo" << endl;
            // delete end;
        }
        else
        {
            cout << "INVALID MOVE\n";
            return false;
        }
        return true;
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
    cout << "Game Start" << endl
         << endl;
    board.display();
    bool WhiteTurn = true;
    while (1)
    {
        if (WhiteTurn)
            cout << "White to move : " << endl;
        else
            cout << "Black to move : " << endl;

        string in1, in2;
        cout << "   Enter starting pos :";
        getline(cin, in1);
        cout << "   Enter ending pos :";
        getline(cin, in2);
        if (board.move(in1, in2, WhiteTurn))
            WhiteTurn = (!WhiteTurn);
        cout << endl;
        board.display();
        cout << endl;
    }
    return 0;
}
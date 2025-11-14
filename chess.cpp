#include <iostream>
#include <windows.h>

using namespace std;

class pieces
{
protected:
    bool iswhite;

public:
    string name;
    bool hasmoved;
    pieces(string na, bool col, bool hm=false)
    {
        iswhite = col;
        name = na;
        hasmoved = hm;
    }
    virtual bool isvalid(int sti, int stj, int endi, int endj, bool col, pieces ***grid) const = 0;
    bool isWhite() const { return iswhite; }
};
class rook : public pieces
{
public:
    rook(bool col) : pieces("ROOK", col, false) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (sti == endi) {
            int step = (endj > stj) ? 1 : -1;
            for (int j = stj + step; j != endj; j += step)
                if (grid[sti][j] != nullptr) return false;
        } 
        else if (stj == endj) {
            int step = (endi > sti) ? 1 : -1;
            for (int i = sti + step; i != endi; i += step)
                if (grid[i][stj] != nullptr)
                    return false;
        } 
        else return false;
        if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == iswhite)
            return false;
        return true;
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
        if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == iswhite) return false;
        return true;
    }
};
class king : public pieces
{
    bool can_cas = true;

public:
    king(bool col) : pieces("KING", col, false) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        int dx = abs(sti - endi);
        int dy = abs(stj - endj);
        if (dx <= 1 && dy <= 1 && !(dx == 0 && dy == 0)){ 
            if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == iswhite) return false;

            return true;
        }
        if (!hasmoved && dx == 0 && dy == 2 && sti == endi) return true; 
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
        if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == iswhite) return false;
        return true;
    }
};

class pawn : public pieces
{
public:
    pawn(bool col) : pieces("PAWN", col) {};
    bool isvalid(int sti, int stj, int endi, int endj, bool iswhite, pieces ***grid) const override
    {
        if (endj == stj) // normal move
        {
            if (!isWhite())
            {
                if (sti == 1)
                {
                    if ((endi == sti + 2 and grid[sti + 2][endj] == nullptr and grid[sti + 1][endj] == nullptr) or (endi == sti + 1 and grid[sti + 1][endj] == nullptr))
                        return true;
                }
                else if (endi == sti + 1 and grid[sti + 1][endj] == nullptr)

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
        else 
        {
            if (isWhite())
            {
                if (sti - 1 == endi and (stj - 1 == endj or stj + 1 == endj))
                {
                    if (grid[endi][endj] != nullptr and !(grid[endi][endj]->isWhite()))
                        return true;
                }
            }
            else
            {
                if (sti + 1 == endi and (stj - 1 == endj or stj + 1 == endj))
                {
                    if (grid[endi][endj] != nullptr and grid[endi][endj]->isWhite())
                        return true;
                }
            }
        }

        return false;
    }
};

class Board
{
private:
    pieces ***grid;
    bool gameOver=false;
    friend class pieces;

public:
    bool Gameover(){
        return gameOver;
    }
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

    bool handle_castling(int sti, int stj, int endi, int endj, bool whiteTurn){
        bool kingside = (endj > stj);
        int rookCol = kingside ? 7 : 0;
        int rooknewpos = kingside ? endj - 1 : endj + 1;
    
        pieces* rook = grid[sti][rookCol];
        if (!rook || rook->name != "ROOK" || rook->hasmoved || rook->isWhite() != whiteTurn) {
            cout << "Cannot castle - rook issue!\n";
            return false;
        }
    
        int step = kingside ? 1 : -1;
        for (int j = stj + step; j != rookCol; j += step) {
            if (grid[sti][j] != nullptr) {
                cout << "Cannot castle - pieces in the way!\n";
                return false;
            }
        }
    
        if (king_in_check(whiteTurn)) {
            cout << "Cannot castle, king is in check!\n";
            return false;
        }
    
        pieces* tempKing = grid[sti][stj];
        grid[sti][stj] = nullptr;
        grid[sti][stj + step] = tempKing;
        
        if (king_in_check(whiteTurn)){
            grid[sti][stj] = tempKing;
            grid[sti][stj + step] = nullptr;
            cout << "Cannot castle, king would pass through check!\n";
            return false;
        }
        else if(!kingside){
            grid[sti][stj+step] = nullptr;
            grid[sti][stj + 2*step] = tempKing;
            if (king_in_check(whiteTurn)){
                grid[sti][stj] = tempKing;
                grid[sti][stj + 2*step] = nullptr;
                cout << "Cannot castle, king would pass through check!\n";
                return false;
            }
        }
        grid[sti][stj] = tempKing;
        grid[sti][stj+step] = nullptr;
    
        grid[endi][endj] = grid[sti][stj];
        grid[sti][stj] = nullptr;
        grid[endi][endj]->hasmoved = true;
    
        grid[sti][rooknewpos] = rook;
        grid[sti][rookCol] = nullptr;
        grid[sti][rooknewpos]->hasmoved = true;
    
        cout << "Castled!" << endl;
        return true;
    }

    ~Board()
    {
        cout << "Good Game" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                delete grid[i][j];
            }
            delete grid[i];
        }
        delete grid;
    }

    bool isPromotion(string name, int endi, bool iswhite)
    {
        if (name != "PAWN")
            return false;

        if (endi == 7 and !iswhite)
            return true;
        else if (endi == 0 and iswhite)
            return true;

        return false;
    }

    void makePromotion(int endi, int endj, pieces ***grid, bool white)
    {
        while (true)
        {
            string p;
            cout << "Which Piece you want to make?" << endl
                 << "1. Queen" << endl
                 << "2. Rook" << endl
                 << "3. Knight" << endl
                 << "4. Bishop" << endl
                 << "Enter the Number [1,2,3,4] : ";

            getline(cin, p);

            if (p != "1" and p != "2" and p != "3" and p != "4")
            {
                cout << "Invalid Input!!" << endl;
                continue;
            }

            if (p == "1")
            {
                delete grid[endi][endj];
                grid[endi][endj] = new queen(white);
                break;
            }
            if (p == "2")
            {
                delete grid[endi][endj];
                grid[endi][endj] = new rook(white);
                break;
            }
            if (p == "3")
            {
                delete grid[endi][endj];
                grid[endi][endj] = new knight(white);
                break;
            }
            if (p == "4")
            {
                delete grid[endi][endj];
                grid[endi][endj] = new bishop(white);
                break;
            }
        }
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
    pair<int, int> king_position(bool white)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (grid[i][j] && grid[i][j]->isWhite() == white && grid[i][j]->name == "KING") return {i, j};
        return {-1, -1};
    }
    bool king_in_check(bool white)
    {
        pair<int, int> king;
        king = king_position(white);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (grid[i][j] != nullptr && grid[i][j]->isWhite() != white)
                {
                    if (grid[i][j]->isvalid(i, j, king.first, king.second, grid[i][j]->isWhite(), grid))
                        return true;
                }
            }
        }
        return false;
    }
    bool no_legal_moves(bool white){
        // cout << "Checking legal moves for " << (white ? "white" : "black") << endl;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                pieces* p = grid[i][j];
                if (p == nullptr || p->isWhite() != white) continue;
                for(int x = 0; x < 8; x++){
                    for(int y = 0; y < 8; y++){
                        if(x==i && y==j) continue;
                        if (!p->isvalid(i, j, x, y, p->isWhite(), grid)) continue;
                        if (grid[x][y] != nullptr && grid[x][y]->isWhite() == p->isWhite()) continue;
                        pieces* captured = grid[x][y];
                        grid[x][y] = p;
                        grid[i][j] = nullptr;
                        bool op=king_in_check(white);
                        grid[i][j] = p;
                        grid[x][y] = captured;
                        if(!op) return false;
                        // cout << "Found at least one valid move for " << (white ? "white" : "black") << endl;
                    }
                }
            }
        }
        // cout << "No legal moves detected for " << (white ? "white" : "black") << endl;
        return true;
    }
    bool move(string st, string end, bool whiteTurn)
    {
        int stj = st[0] - 'a', sti = 8 - (st[1] - '0'), endj = end[0] - 'a', endi = 8 - (end[1] - '0');

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
        else if (grid[sti][stj]->isWhite() != whiteTurn)
        {
            cout << "INVALID MOVE" << endl;
            cout << "It's not your piece" << endl;
            return false;
        }
        if (grid[sti][stj]->isvalid(sti, stj, endi, endj, grid[sti][stj]->isWhite(), grid))
        {
            if (grid[sti][stj]->name == "KING" && abs(stj - endj) == 2){
                return handle_castling(sti, stj, endi, endj, whiteTurn);
            }
            if (grid[endi][endj] != nullptr && grid[endi][endj]->isWhite() == grid[sti][stj]->isWhite())
            {
                cout << "Cannot capture your own piece!\n";
                return false;
            }
            pieces *end = grid[endi][endj];
            grid[endi][endj] = grid[sti][stj];
            grid[sti][stj] = nullptr;

            if (isPromotion(grid[endi][endj]->name, endi, grid[endi][endj]->isWhite()))
            {
                makePromotion(endi, endj, grid, grid[endi][endj]->isWhite());
            }

            if (king_in_check(whiteTurn))
            {
                cout << "INVALID MOVE YOUR KING WOULD BE IN CHECK";
                grid[sti][stj] = grid[endi][endj];
                grid[endi][endj] = end;
                return false;
            }
            else if (king_in_check(!whiteTurn))
            {
                cout<<"Check";
                if(no_legal_moves(!whiteTurn)){
                    cout<<" mate!!"<<endl;
                    gameOver = true; 
                    return true;
                }
                cout<<endl;
                return true;
            }
            delete end;
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
        SetConsoleOutputCP(CP_UTF8);
        for (int r = 0; r < 8; r++)
        {
            cout << (8 - r) << " |";
            for (int c = 0; c < 8; c++)
            {
                if (grid[r][c] == nullptr)
                {
                    if (r % 2 == c % 2)
                        cout << u8" ■ ";
                    // else cout << "\033[2;92m" << " % " << "\033[0m";
                    else
                        cout << "\033[2;92m" << u8" ■ " << "\033[0m";
                }
                else
                {
                    if (grid[r][c]->isWhite())
                    {
                        cout << " W";
                        cout << grid[r][c]->name[0];
                    }
                    else
                    {
                        cout << "\033[31m" << " B" << grid[r][c]->name[0] << "\033[0m";
                    }
                }
            }
            cout << " | " << (8 - r) << "\n";
        }
        cout << "  -------------------------\n";
        cout << "    a  b  c  d  e  f  g  h\n";
    }
}; 
class game{
    protected:
    bool isWhite;
    int timeleft;
    public:
    game(){};
    game(bool isw, int t = 30){
        isWhite = isw;
        timeleft = t;
    }
};
class Player: public game
{
private:
    string name;

public:
    Player(){};
    Player(bool isw, int t = 30):game(isw,t)
    {
        name="";
    }
    string getname() { return name; }
    bool iswhiteside() { return isWhite; }
    int gettime() { return timeleft; }
    Player operator+(string n){
        Player temp;
        temp.isWhite=this->isWhite;
        temp.timeleft=this->timeleft;
        temp.name=n;
        return temp;
    }
};


int main()
{
    Player p1(false, 30);
    Player p2(true, 30);
    p1=p1+"Jeel";
    p2=p2+"Neel";
    cout << p1.getname() << " " << (p1.iswhiteside() ? "is white" : "is black") << endl;
    cout << p2.getname() << " " << (p2.iswhiteside() ? "is white" : "is black") << endl;
    Board board;
    cout << "Game Start" << endl
         << endl;
    board.display();
    bool WhiteTurn = true;
    while (true)
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
        if(board.Gameover()) break;
        board.display();
        cout << endl;
    }
    return 0;
}
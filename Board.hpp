#include <bits/stdc++.h>
#include "Solve.hpp"
using namespace std;
class Chess{
private:
    Color color;
    wchar_t chess;
public:
    Color gColor(){ return color; }
    wchar_t gChess(){ return chess; }
    void changeColor(Color col){ color=col; }
    void changeChess(wchar_t _chess){ chess=_chess; }
};
class Board{
private:
    Chess board[105][105];
public:
    Chess gBoard(int x,int y){ return board[x][y]; }
    wchar_t gChess(int x,int y){ return board[x][y].gChess(); }
    Color gColor(int x,int y){ return board[x][y].gColor(); }
};
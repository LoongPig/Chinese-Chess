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
    void change(Chess che){ color=che.gColor(),chess=che.gChess(); }
    Chess(Color col=null,wchar_t che=blank){ color=col,chess=che; }
    void print(){
        if(color==red) colorString(244);
        if(color==black) colorString(240);
        wcout<<chess;
        if(chess==blank) wcout<<L" ";
        colorString(240);
    }
};
struct opt{
    int x,y;
    Chess _chess;
    opt(int _x,int _y,Chess _che){ x=_x,y=_y,_chess=_che; }
};

class Board{
private:
    Chess board[15][15];
public:
    Chess gBoard(int x,int y){ return board[x][y]; }
    wchar_t gChess(int x,int y){ return board[x][y].gChess(); }
    Color gColor(int x,int y){ return board[x][y].gColor(); }
    void Move(int x,int y,int a,int b){ board[a][b].change(board[x][y]);board[x][y].change(Chess()); }// x,y => a,b
    template<typename... Args>
    void Change(Args... _op) { (void(board[_op.x][_op.y].change(_op._chess)), ...); }
    Board(){
        Change(
            opt(1,1,Chess(red,L'车')),opt(1,9,Chess(red,L'车')),
            opt(1,2,Chess(red,L'马')),opt(1,8,Chess(red,L'马')),
            opt(1,3,Chess(red,L'相')),opt(1,7,Chess(red,L'相')),
            opt(1,4,Chess(red,L'士')),opt(1,6,Chess(red,L'士')),
            opt(3,2,Chess(red,L'炮')),opt(3,8,Chess(red,L'炮')),

            opt(10,1,Chess(black,L'車')),opt(10,9,Chess(black,L'車')),
            opt(10,2,Chess(black,L'馬')),opt(10,8,Chess(black,L'馬')),
            opt(10,3,Chess(black,L'象')),opt(10,7,Chess(black,L'象')),
            opt(10,4,Chess(black,L'仕')),opt(10,6,Chess(black,L'仕')),
            opt(8,2,Chess(black,L'炮')),opt(8,8,Chess(black,L'炮')),

            opt(1,5,Chess(red,L'帅')),opt(10,5,Chess(black,L'将')));
        for(int i=1;i<=9;i+=2) Change(opt(4,i,Chess(red,L'卒')),opt(7,i,Chess(black,L'兵')));
    }
    void print(){
        for(int i=1;i<=10;i++){
            for(int j=1;j<=9;j++)
                board[i][j].print();
            wcout<<L"\n";
        }
    }
};
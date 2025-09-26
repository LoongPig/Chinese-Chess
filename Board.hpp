#pragma once
#include <bits/stdc++.h>
#include "Solve.hpp"
using namespace std;
struct coord{
    int x,y;
    coord(int _x=-1,int _y=-1){ x=_x,y=_y; }
    bool operator==(coord other)const{
        return x==other.x&&y==other.y;
    }
};
class Chess{
private:
    Color color;
    wchar_t chess;
    bool flag;
public:
    Color gColor(){ return color; }
    wchar_t gChess(){ return chess; }
    void changeColor(Color col){ color=col; }
    void changeChess(wchar_t _chess){ chess=_chess; }
    void change(Chess che){ color=che.gColor(),chess=che.gChess(); }
    Chess(Color col=null,wchar_t che=blank){ color=col,chess=che,flag=false; }
    void highLight(){ flag=true; }
    void lowLight(){ flag=false; }
    void print(){
        if(color==red) colorString(244);
        if(color==black) colorString(240);
        if(flag) colorString(246);
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
    int StepCnt;
public:
    Chess gBoard(int x,int y){ return board[x][y]; }
    wchar_t gChess(int x,int y){ return board[x][y].gChess(); }
    wchar_t gChess(coord _){ return gChess(_.x,_.y); }
    Color gColor(int x,int y){ return board[x][y].gColor(); }
    Color gColor(coord _){ return gColor(_.x,_.y); }
    void Move(int x,int y,int a,int b){ board[a][b].change(board[x][y]);board[x][y].change(Chess()); }// x,y => a,b
    template<typename... Args>
    void Change(Args... _op) { (void(board[_op.x][_op.y].change(_op._chess)), ...); }
    Board(){
        StepCnt=0;
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
        gotoXY(0,0);
        for(int i=1;i<=10;i++){
            for(int j=1;j<=9;j++)
                board[i][j].print();
            wcout<<L"\n";
        }
    }
    coord selectChess(){
        static coord pla={1,1};
        while(!key_down(VK_RETURN)){
            coord tmp=pla;
            if(key_down(VK_UP)||key_down('W')) pla.x=max(1,pla.x-1);
            if(key_down(VK_LEFT)||key_down('A')) pla.y=max(1,pla.y-1);
            if(key_down(VK_RIGHT)||key_down('D')) pla.y=min(9,pla.y+1);
            if(key_down(VK_DOWN)||key_down('S')) pla.x=min(10,pla.x+1);
            if(tmp==pla) continue;
            board[tmp.x][tmp.y].lowLight();
            board[pla.x][pla.y].highLight();
            print();
            Sleep(60);
        }
        return pla;
    }
    bool checkWay(coord s,coord e){
        auto [sx,sy]=s; auto [ex,ey]=e;
        if(s==e||gColor(s)==null||gColor(s)==gColor(e)) return false;
        if(gChess(s)==L'将'||gChess(s)==L'帅'){
            if(abs(sx-ex)+abs(sy-ey)==1) return true;
            else return false;
        }
        if(gChess(s)==L'车'||gChess(s)==L'車'){
            if(sx==ex||sy==ey) return true;
            else return false;
        }
        if(gChess(s)==L'马'||gChess(s)==L'馬'){
            int dx[]={1,1,-1,-1,2,2,-2,-2};
            int dy[]={2,-2,2,-2,1,-1,1,-1};
            for(int i=0;i<8;i++)
                if(sx+dx[i]==ex&&sy+dy[i]==ey){
                    if(abs(dx[i])==2) return gColor(sx+dx[i]/2,sy)==null;
                    else return gColor(sx,sy+dy[i]/2)==null;
                }
            return false;
        }
        if(gChess(s)==L'相'||gChess(s)==L'象'){
            
        }
        if(gChess(s)==L'士'||gChess(s)==L'仕'){

        }
        if(gChess(s)==L'炮'||gChess(s)==L'炮'){

        }
        if(gChess(s)==L'兵'||gChess(s)==L'卒'){

        }
    }
};
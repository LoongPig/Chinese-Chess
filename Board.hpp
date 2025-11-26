<<<<<<< HEAD
#ifndef BOARD_HPP
#define BOARD_HPP

#include <bits/stdc++.h>
#include "Basic.hpp"
using namespace std;

namespace N_Board{
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
        bool flag;// Is or is not highlight
    public:
        Color gColor(){ return color; }// get Color
        wchar_t gChess(){ return chess; }// get Chess
        void changeColor(Color col){ color=col; }// change Color
        void changeChess(wchar_t _chess){ chess=_chess; }// change Color
        void change(Chess che){ color=che.gColor(),chess=che.gChess(); }// change color and chess
        Chess(Color col=null,wchar_t che=blank){ color=col,chess=che,flag=false; }
        void highLight(){ flag=true; }
        void lowLight(){ flag=false; }
        void print(){
            // switch color
            if(color==red) colorString(244);
            if(color==black) colorString(240);
            if(flag) colorString(246);
            wcout<<chess;
            if(chess==blank) wcout<<L" ";
            colorString(240);// turn to start
        }
    };
    struct opt{//  The options
        int x,y;
        Chess _chess;
        opt(int _x,int _y,Chess _che){ x=_x,y=_y,_chess=_che; }
    };

    class Board{
    private:
        Chess board[15][15];
        int StepCnt;
        coord redMaster,blackMaster;// Place of them
    public:
        Chess gBoard(int x,int y){ return board[x][y]; }// get Board(x,y)
        wchar_t gChess(int x,int y){ return board[x][y].gChess(); }// get Board(x,y)'s chess
        wchar_t gChess(coord _){ return gChess(_.x,_.y); }
        Color gColor(int x,int y){ return board[x][y].gColor(); }
        Color gColor(coord _){ return gColor(_.x,_.y); }
        coord gMaster(Color col){// get the master place
            if(col==red) return redMaster;
            return blackMaster; 
        }
        void changeMaster(Color col,int x,int y){// change the place
            if(col==red) redMaster=coord(x,y);
            else blackMaster=coord(x,y);
        }
        void Move(int x,int y,int a,int b){ board[a][b].change(board[x][y]);board[x][y].change(Chess()); }//  x,y => a,b
        void Move(coord s,coord e){ Move(s.x,s.y,e.x,e.y); }
        int rowCount(int x,int sy,int ey){// count how many chess are there on sy~ey on the X row
            if(sy>ey) swap(sy,ey); 
            int cnt=0;
            for(int i=sy;i<=ey;i++) cnt+=(gColor(x,i)!=null);
            return cnt; 
        }//  包含 sy,ey
        int colCount(int y,int sx,int ex){ // 同上
            if(sx>ex) swap(sx,ex);
            int cnt=0;
            for(int i=sx;i<=ex;i++) cnt+=(gColor(i,y)!=null);
            return cnt; 
        }//  包含 sx,ex
        template<typename... Args>
        void Change(Args... _op) { ((board[_op.x][_op.y].change(_op._chess)), ...); }// solve the opt
        Board(){
            StepCnt=0,redMaster=coord(1,5),blackMaster=coord(10,5);
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
            for(int i=1;i<=9;i+=2) Change(opt(4,i,Chess(red,L'兵')),opt(7,i,Chess(black,L'卒')));
        }
        void print(){// print Board
            gotoXY(0,0);
            // /*
            wcout<<L"WASD 或 ↑,↓,←,→ 移动，Enter 确定，ESC 退出\n";
            // */
            for(int i=1;i<=10;i++){
                for(int j=1;j<=9;j++)
                    board[i][j].print();
                wcout<<L"\n";
            }
            for(int i=1;i<=10;i++){
                for(int j=1;j<=20;j++) wcout<<L" ";
                wcout<<L"\n";
            }
        }
        coord selectChess(){// select a chess
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
            print();
            return pla;
        }
        bool checkWay(coord s,coord e){// check the chess way is it ok.
            auto [sx,sy]=s; auto [ex,ey]=e;
            if(s==e||gColor(s)==null||gColor(s)==gColor(e)) return false;
            if(gChess(s)==L'将'||gChess(s)==L'帅'){
                if(abs(sx-ex)+abs(sy-ey)==1){
                    changeMaster(gColor(s),ex,ey);
                    return true;
                }
                else return false;
            }
            if(gChess(s)==L'车'||gChess(s)==L'車'){
                if(sx!=ex&&sy!=ey) return false;
                if(sx==ex&&rowCount(sx,sy,ey)==1+(gColor(e)!=null)) return true; // 车和被吃的棋子
                else if(sy==ey&&colCount(sy,sx,ex)==1+(gColor(e)!=null)) return true;
                return false;
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
                int dx[]={2,2,-2,-2};
                int dy[]={-2,2,-2,2};
                for(int i=0;i<4;i++)
                    if(sx+dx[i]==ex&&sy+dy[i]==ey)
                        return gColor(sx+dx[i]/2,sy+dy[i]/2)==null;
                return false;
            }
            if(gChess(s)==L'士'||gChess(s)==L'仕'){
                int dx[]={1,1,-1,-1};
                int dy[]={-1,1,-1,1};
                bool flag=false;
                for(int i=0;i<4;i++) flag|=(sx+dx[i]==ex&&sy+dy[i]==ey);
                return flag;                
            }
            if(gChess(s)==L'炮'||gChess(s)==L'炮'){
                if(sx!=ex&&sy!=ey) return false;
                if(sx==ex&&rowCount(sx,sy,ey)==1+(gColor(e)!=null)*2) return true;
                if(sy==ey&&colCount(sy,sx,ex)==1+(gColor(e)!=null)*2) return true;
                return false;
            }
            if(gChess(s)==L'兵'||gChess(s)==L'卒'){
                if(gChess(s)==L'卒') return (sx>5&&sx-ex==1&&sy==ey)||(sx<=5&&sx-ex+abs(sy-ey)==1);
                else return (sx<6&&ex-sx==1&&sy==ey)||(sx>=6&&ex-sx+abs(sy-ey)==1);
            }
            return false;
        }
        bool checkMaster(Color col){// 判将军，已将为 true
            for(int i=1;i<=10;i++)
                for(int j=1;j<=9;j++)
                    if(gColor(i,j)==gOppoColor(col))
                        if(checkWay(coord(i,j),gMaster(col))) return true;
            return false;
        }
        void play(){// Start game function
            print();
            while(!key_down(VK_ESCAPE)){
                RedStart:
                MessageBox(NULL,L"红方移动",L"提示",MB_OK);
                coord p1=selectChess();
                if(gColor(p1)!=red) goto RedStart;
                MessageBox(NULL,L"棋子要去哪",L"提示",MB_OK);
                coord p2=selectChess();
                if(!checkWay(p1,p2)) goto RedStart;
                Move(p1,p2);
                BlackStart:
                MessageBox(NULL,L"黑方移动",L"提示",MB_OK);
                p1=selectChess();
                if(gColor(p1)!=black) goto BlackStart;
                MessageBox(NULL,L"棋子要去哪",L"提示",MB_OK);
                p2=selectChess();
                if(!checkWay(p1,p2)) goto BlackStart;
                Move(p1,p2);
            }
        }
    };
}
using namespace N_Board;
#endif
=======
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
    void Move(coord s,coord e){ Move(s.x,s.y,e.x,e.y); }
    int rowCount(int x,int sy,int ey){
        if(sy>ey) swap(sy,ey); 
        int cnt=0;
        for(int i=sy;i<=ey;i++) cnt+=(gColor(x,i)!=null);
        return cnt; 
    }// 包含 sy,ey
    int colCount(int y,int sx,int ex){ 
        if(sx>ex) swap(sx,ex);
        int cnt=0;
        for(int i=sx;i<=ex;i++) cnt+=(gColor(i,y)!=null);
        return cnt; 
    }// 包含 sx,ex
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
        for(int i=1;i<=9;i+=2) Change(opt(4,i,Chess(red,L'兵')),opt(7,i,Chess(black,L'卒')));
    }
    void print(){
        gotoXY(0,0);
        for(int i=1;i<=10;i++){
            for(int j=1;j<=9;j++)
                board[i][j].print();
            wcout<<L"\n";
        }
        for(int i=1;i<=10;i++){
            for(int j=1;j<=20;j++) wcout<<L" ";
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
            if(sx!=ex&&sy!=ey) return false;
            if(sx==ex&&rowCount(sx,sy,ey)==1+(gColor(e)!=null)) return true; //车和被吃的棋子
            else if(sy==ey&&colCount(sy,sx,ex)==1+(gColor(e)!=null)) return true;
            return false;
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
            int dx[]={2,2,-2,-2};
            int dy[]={-2,2,-2,2};
            for(int i=0;i<4;i++)
                if(sx+dx[i]==ex&&sy+dy[i]==ey)
                    return gColor(sx+dx[i]/2,sy+dy[i]/2)==null;
            return false;
        }
        if(gChess(s)==L'士'||gChess(s)==L'仕'){
            int dx[]={1,1,-1,-1};
            int dy[]={-1,1,-1,1};
            bool flag=false;
            for(int i=0;i<4;i++) flag|=(sx+dx[i]==ex&&sy+dy[i]==ey);
            return flag;                
        }
        if(gChess(s)==L'炮'||gChess(s)==L'炮'){
            if(sx!=ex&&sy!=ey) return false;
            if(sx==ex&&rowCount(sx,sy,ey)==1+(gColor(e)!=null)*2) return true;
            if(sy==ey&&colCount(sy,sx,ex)==1+(gColor(e)!=null)*2) return true;
            return false;
        }
        if(gChess(s)==L'兵'||gChess(s)==L'卒'){
            if(gChess(s)==L'卒') return (sx>5&&sx-ex==1&&sy==ey)||(sx<=5&&sx-ex+abs(sy-ey)==1);
            else return (sx<6&&ex-sx==1&&sy==ey)||(sx>=6&&ex-sx+abs(sy-ey)==1);
        }
        return false;
    }
};
void PlayOn(Board &_const_){
    _const_.print();
    while(!key_down(VK_ESCAPE)){
        RedStart:
        MessageBox(NULL,L"Red select move chess",L"Prompt",MB_OK);
        coord p1=_const_.selectChess();
        if(_const_.gColor(p1)!=red) goto RedStart;
        MessageBox(NULL,L"Red select where to go",L"Prompt",MB_OK);
        coord p2=_const_.selectChess();
        if(!_const_.checkWay(p1,p2)) goto RedStart;
        _const_.Move(p1,p2);
        BlackStart:
        MessageBox(NULL,L"Black select move chess",L"Prompt",MB_OK);
        p1=_const_.selectChess();
        if(_const_.gColor(p2)!=black) goto BlackStart;
        MessageBox(NULL,L"Black select where to go",L"Prompt",MB_OK);
        p2=_const_.selectChess();
        if(!_const_.checkWay(p1,p2)) goto BlackStart;
        _const_.Move(p1,p2);
    }
}
>>>>>>> 2f864cf7b08f032f22dbbb7695c7fd1155f48603

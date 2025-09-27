#include <bits/stdc++.h>
#include "Solve.hpp"
#include "Board.hpp"
using namespace std;
int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    hideCursor(),system("color f0"),gotoXY(0,0);
    Board _const;
    for(int i=1;i<=10;i++){
        coord p1=_const.selectChess();
        coord p2=_const.selectChess();
        wcout<<p1.x<<L" "<<p1.y<<L" "<<p2.x<<L" "<<p2.y<<L" "<<_const.checkWay(p1,p2)<<endl;
    }
    system("pause");
    return 0;
}
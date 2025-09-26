#include <bits/stdc++.h>
#include "Solve.hpp"
#include "Board.hpp"
using namespace std;
int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    hideCursor(),system("color f0"),gotoXY(0,0);
    Board _const;
    _const.print();
    system("pause");
    return 0;
}
#include <bits/stdc++.h>
#include "Solve.hpp"
#include "Board.hpp"
using namespace std;
int main(){
    start();
    Board _const_;
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
    system("pause");
    return 0;
}
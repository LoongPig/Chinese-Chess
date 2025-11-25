#ifndef UNICODE
#define UNICODE
#endif

#ifndef BASIC_HPP
#define BASIC_HPP

#include <io.h>
#include <conio.h>
#include <fcntl.h>
#include <codecvt>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

namespace n_Basic{
    #define key_down(VK_NONAME)((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
    const HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
    const HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    enum Color{red,black,null};//all colors
    const wchar_t blank=L'+';
    void hideCursor(){ //hide the cursor
        const CONSOLE_CURSOR_INFO info={1,FALSE}; 
        SetConsoleCursorInfo(hOut,&info); 
    }
    void gotoXY(short row,short line){ //screen goto(x,y)
        SetConsoleCursorPosition(hOut,(COORD){line,row}); 
    }
    void colorString(int col){//set color
        SetConsoleTextAttribute(hOut,col);
    }
    void selectMode();
    void start(){
        _setmode(_fileno(stdout),_O_U16TEXT);//Set UTF-8
        hideCursor(),system("color f0"),gotoXY(0,0);//Init
        //Print TUI
        wcout<<L"Chinese-Chess v1.0.3\n";  
        thread t([&]{//check yes/not press ESC
            while(1){
                if(key_down(VK_ESCAPE))
                    if(MessageBox(NULL,L"你确定要退出吗？",L"询问",MB_YESNO)==IDYES) exit(0);
                Sleep(55);
            }
        }); t.detach();
    }
    std::wstring StrToWstr(const std::string& s){
        if(s.empty()) return L"";
        int SZ_nd=MultiByteToWideChar(CP_UTF8,0,s.c_str(),(int)s.size(),nullptr,0);
        std::wstring res(SZ_nd,0);
        MultiByteToWideChar(CP_UTF8,0,s.c_str(),(int)s.size(),&res[0],SZ_nd);
        return res;
    }
    std::string WstrToStr(const std::wstring& s){
        if(s.empty()) return "";
        int SZ_nd=WideCharToMultiByte(CP_UTF8,0,s.c_str(),(int)s.size(),nullptr,0,nullptr,nullptr);
        std::string res(SZ_nd,0);
        WideCharToMultiByte(CP_UTF8,0,s.c_str(),(int)s.size(),&res[0],SZ_nd,nullptr,nullptr);
        return res;
    }
    Color gOppoColor(Color col){ //get the opposite color
        if(col==null) return null; 
        return(col==red?black:red); 
    }
}
using namespace n_Basic;
#endif
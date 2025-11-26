#ifndef UNICODE
#define UNICODE
#endif

#ifndef BASIC_HPP
#define BASIC_HPP

#include <io.h>
#include <format>
#include <conio.h>
#include <fcntl.h>
#include <codecvt>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

// The functions' def:

namespace n_Basic{
    #define key_down(VK_NONAME)((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
    const HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
    const HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    enum Color{red,black,null};// all colors
    const wchar_t blank=L'+';
    void hideCursor(); //hide the cursor
    void gotoXY(short row,short line); // screen goto(x,y)
    void colorString(int col); // set color
    void selectMode();
    void start();
    wstring StrToWstr(const string& s);
    string WstrToStr(const wstring& s);
    Color gOppoColor(Color col); // get the opposite color
    template<typename T>
    struct coord{ // the struct of coordinate
        T x,y;
        coord<T>(T _x=-1,T _y=-1)
            :x(_x),y(_y){}
        bool operator==(coord other)const{ return x==other.x&&y==other.y; }
        string to_string();
    };
    void flashWin(HWND hwnd); // the function to flash window
}

// The Implementation of the function above this sentence:

template<typename T>
string n_Basic::coord<T>::to_string(){
    ostringstream oss;
    if(is_floating_point_v<T>) oss<<fixed<<setprecision(3)<<x<<" "<<y;
    else if(is_integral_v<T>) oss<<x<<" "<<y;
    else return "Error";
    return oss.str();
}
void n_Basic::hideCursor(){
    const CONSOLE_CURSOR_INFO info={1,FALSE}; 
    SetConsoleCursorInfo(hOut,&info); 
}
void n_Basic::gotoXY(short row,short line){
    SetConsoleCursorPosition(hOut,(COORD){line,row}); 
}
void n_Basic::start(){
    _setmode(_fileno(stdout),_O_U16TEXT);// Set UTF-8
    hideCursor(),system("color f0"),gotoXY(0,0);// Init
    // Print TUI
    wcout<<L"Chinese-Chess v1.0.3\n";  
    thread t([&]{// check yes/not press ESC
        while(1){
            if(key_down(VK_ESCAPE))
                if(MessageBox(NULL,L"你确定要退出吗？",L"询问",MB_YESNO)==IDYES) exit(0);
            Sleep(55);
        }
    }); t.detach();
}
wstring n_Basic::StrToWstr(const string& s){
    if(s.empty()) return L"";
    int SZ_nd=MultiByteToWideChar(CP_UTF8,0,s.c_str(),(int)s.size(),nullptr,0);
    wstring res(SZ_nd,0);
    MultiByteToWideChar(CP_UTF8,0,s.c_str(),(int)s.size(),&res[0],SZ_nd);
    return res;
}
string n_Basic::WstrToStr(const wstring& s){
    if(s.empty()) return "";
    int SZ_nd=WideCharToMultiByte(CP_UTF8,0,s.c_str(),(int)s.size(),nullptr,0,nullptr,nullptr);
    string res(SZ_nd,0);
    WideCharToMultiByte(CP_UTF8,0,s.c_str(),(int)s.size(),&res[0],SZ_nd,nullptr,nullptr);
    return res;
}
n_Basic::Color n_Basic::gOppoColor(Color col){
    if(col==null) return null; 
    return(col==red?black:red); 
}
void n_Basic::colorString(int col){// set color
    SetConsoleTextAttribute(hOut,col);
}
void n_Basic::flashWin(HWND hwnd){ // the function to flash window
    if(IsIconic(hwnd)) FlashWindow(hwnd,TRUE);
    else if(hwnd!=GetForegroundWindow()) FlashWindow(hwnd,TRUE);
}
using namespace n_Basic;
#endif
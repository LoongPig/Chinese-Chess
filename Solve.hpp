#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#include <io.h>
#include <conio.h>
#include <fcntl.h>
#include <codecvt>
#include <windows.h>
#include <bits/stdc++.h>
#define key_down(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
const HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
const HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
enum Color{red,black,null};//all colors
const wchar_t blank=L'+';
void hideCursor(){ //hide the cursor
    const CONSOLE_CURSOR_INFO info={1,FALSE}; 
    SetConsoleCursorInfo(hOut,&info); 
}
void gotoXY(short row,short line){ //screen goto (x,y)
    SetConsoleCursorPosition(hOut,(COORD){line,row}); 
}
void colorString(int col){//set color
	SetConsoleTextAttribute(hOut,col);
}
void start(){
    _setmode(_fileno(stdout), _O_U16TEXT);//Set UTF-8
    hideCursor(),system("color f0"),gotoXY(0,0);//Init
}
wstring StrToWstr(string s){
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}
string WstrToStr(wstring s){
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(s);
}
Color gAntColor(Color col){ if(col==null) return null; return (col==red?black:red); }//get the opposite color
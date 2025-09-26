#pragma once
#include <io.h>
#include <conio.h>
#include <fcntl.h>
#include <windows.h>
#include <bits/stdc++.h>
#ifdef UNICODE
#define UNICODE
#endif
#define key_down(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
const HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
const HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
enum Color{red,black,null};
const wchar_t blank=L'+';
void hideCursor(){ 
    const CONSOLE_CURSOR_INFO info={1,FALSE}; 
    SetConsoleCursorInfo(hOut,&info); 
}
void gotoXY(short row,short line){ 
    SetConsoleCursorPosition(hOut,(COORD){line,row}); 
}
void colorString(int col){
	SetConsoleTextAttribute(hOut,col);
}
void cls(int len){
    colorString(255);
    for(int i=1;i<=5000;i++) wcout<<L" ";
}
void setSize(short width,short height){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize={width, height};
    SetConsoleScreenBufferSize(hConsole,bufferSize);
    SMALL_RECT windowSize={0,0,width-1,height-1};
    SetConsoleWindowInfo(hConsole,TRUE,&windowSize);
    HWND hWnd=GetConsoleWindow();
    ShowScrollBar(hWnd,SB_BOTH,FALSE);
}
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <thread>
#include "Basic.hpp"
#include "Board.hpp"
using namespace std;

namespace N_Socket{
    struct Move{ 
        coord<int> S,E; 
        bool valid;
    };
    struct Msg{
        Move mv;
        string to_string();
    };
    Msg to_Msg(string s);
    class Sock{
    private:
        SOCKET own;
        int port;
        bool isServer;
        vector<Msg> msgs;
    public:
        Sock(int _port=80,bool _isServer=1)
            :port(_port),isServer(_isServer){}
        SOCKET gSock(){ return own; }
        int gPort(){ return port; }
        void Exit(); // logout socket
        void Init(); // Init Socket
        void Chatting(); // the function to chat
        bool Connect(const string IP); // the function to connect server
    };
}
string N_Socket::Msg::to_string(){
    return mv.S.to_string()+" "+mv.E.to_string()+" "+(mv.valid?"1":"0");
}
N_Socket::Msg N_Socket::to_Msg(string s){
    std::istringstream iss(s); Msg res; 
    iss>>res.mv.S.x>>res.mv.S.y>>res.mv.E.x>>res.mv.E.y>>res.mv.valid;
    return res;
}
bool N_Socket::Sock::Connect(const string IP){
    sockaddr_in addrIn={};
    addrIn.sin_family=AF_INET;
    addrIn.sin_addr.s_addr=inet_addr(IP.c_str());
    addrIn.sin_port=htons(port);
    if(connect(own,(sockaddr*)(&addrIn),sizeof(addrIn))==INVALID_SOCKET){
        MessageBox(NULL,L"连接失败",L"失败",MB_OK|MB_SYSTEMMODAL);
        return false;
    }
    MessageBox(NULL,L"连接成功",L"提示",MB_OK);
    thread t(Chatting); t.detach(); return true;
}
void N_Socket::Sock::Chatting(){
     while(true){
        char buf[65536];
        if(recv(own,buf,65536,0)<0) break;
        msgs.push_back(to_Msg(string(buf)));
    }
}
void N_Socket::Sock::Exit(){
    closesocket(own);
    WSACleanup();
}
void N_Socket::Sock::Init(){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)){
        MessageBox(NULL,L"Init Socket Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
        exit(0);
    }
    own=socket(AF_INET,SOCK_STREAM,0);
    if(own==INVALID_SOCKET){// Create Socket
        MessageBox(NULL,L"Socket Create Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
        exit(0);
    }
    if(isServer){
        int opt=1;
        setsockopt(own, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
        sockaddr_in addrIn={};
        addrIn.sin_family=AF_INET;
        addrIn.sin_addr.s_addr=INADDR_ANY;
        addrIn.sin_port=htons(port);
        if(bind(own,(sockaddr*)(&addrIn),sizeof(addrIn))==SOCKET_ERROR){// bind
            cerr<<"Bind failed: "<<WSAGetLastError()<<endl;
            MessageBox(NULL,L"Socket Bind Failed!",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
        if(listen(own,5)==INVALID_SOCKET){
            MessageBox(NULL,L"Socket Listen Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
    }
}
using namespace N_Socket;
#endif
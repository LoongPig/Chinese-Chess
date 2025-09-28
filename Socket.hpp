#ifndef UNICODE
#define UNICODE
#endif

#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_
#include <windows.h>
#include <bits/stdc++.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "Solve.hpp"
#include "Board.hpp"
using namespace std;

class Sock{
private:
    SOCKET server;
    int port;
public:
    Sock(int _port=80){ port=_port; }
    SOCKET gSock(){ return server; }
    int gPort(){ return port; }
    void Exit(){//logout socket
        closesocket(server);
        WSACleanup();
    }
    void Init(){//Init Socket
        WSADATA wsaData;
        if(WSAStartup(MAKEWORD(2,2),&wsaData)){
            MessageBox(NULL,L"Init Socket Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
        server=socket(AF_INET,SOCK_STREAM,0);
        if(server==INVALID_SOCKET){//Create Socket
            MessageBox(NULL,L"Socket Create Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
        int opt = 1;
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
        
        sockaddr_in addrIn={};
        addrIn.sin_family=AF_INET;
        addrIn.sin_addr.s_addr=INADDR_ANY;
        addrIn.sin_port=htons(port);
        
        if(bind(server,(sockaddr*)(&addrIn),sizeof(addrIn))==SOCKET_ERROR){//bind
            cerr << "Bind failed: " << WSAGetLastError() << endl;
            MessageBox(NULL,L"Socket Bind Failed!",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
        if(listen(server,5)==INVALID_SOCKET){
            MessageBox(NULL,L"Socket Listen Failed",L"Failed",MB_OK|MB_SYSTEMMODAL);
            exit(0);
        }
    }
    
};
#endif
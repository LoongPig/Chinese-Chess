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
#include "Basic.hpp"
#include "Board.hpp"
using namespace std;

namespace N_Socket{
    class Sock{
    private:
        SOCKET own;
        int port;
        bool isServer;
    public:
        Sock(int _port=80,bool _isServer=1)
            :port(_port),isServer(_isServer){}
        SOCKET gSock(){ return own; }
        int gPort(){ return port; }
        void Exit(){// logout socket
            closesocket(own);
            WSACleanup();
        }
        void Init(){// Init Socket
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
        bool Connect(const string IP){
            sockaddr_in addrIn={};
            addrIn.sin_family=AF_INET;
            addrIn.sin_addr.s_addr=inet_addr(IP.c_str());
            addrIn.sin_port=htons(port);
            if(connect(own,(sockaddr*)(&addrIn),sizeof(addrIn))==INVALID_SOCKET){
                MessageBox(NULL,L"连接失败",L"失败",MB_OK|MB_SYSTEMMODAL);
                return false;
            }
            MessageBox(NULL,L"连接成功",L"提示",MB_OK);

        }
    };
}
using namespace N_Socket;
#endif
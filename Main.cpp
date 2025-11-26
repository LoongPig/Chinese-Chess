#include "Basic.hpp"
#include "Board.hpp"
#include "Socket.hpp"
using namespace std;
int main(){
    start();
    Msg msg={(1,1),(2,2),0};
    cout<<msg.to_string()<<"\n"<<to_Msg(msg.to_string()).to_string();
    system("pause");
    return 0;
}
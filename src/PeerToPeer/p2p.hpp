#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>	
#include <cerrno>
#include <cstring>

#include <iostream>
#include <future>


class SocketHandle{
    public:
        SocketHandle(const std::string& ipAddr, const unsigned int port);
        ~SocketHandle();

        std::string recvData();
        int sendData(const std::string& data);

    private:
        int clientSockFd, serverSockFd, serverSendSockFd;
        const std::string& ipAddr;
        const unsigned int port;

        int initClient(); //to connect to a server 
        int initServer(); //when a client connect check the ip
        
        int runP2PSocket();
        void printError();
};  

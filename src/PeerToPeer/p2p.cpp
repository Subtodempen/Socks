#include "p2p.hpp"
#include <system_error>

#define PORT 9834 //This is the Port that this is running on

SocketHandle::SocketHandle(const std::string& ipAddr, const unsigned int port): ipAddr( ipAddr ), port( port ){
    if(runP2PSocket() == -1)
        throw std::runtime_error("Could not initialize socket");
    
}

SocketHandle::~SocketHandle(){
    shutdown(clientSockFd, SHUT_RDWR);
    shutdown(serverSockFd, SHUT_RDWR);
    shutdown(serverSendSockFd, SHUT_RDWR);
}


int SocketHandle::initClient(){
    sockaddr_in client;
    const socklen_t clientLen = sizeof(sockaddr_in);

    //create socket 
    clientSockFd = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSockFd == -1){
        //error 
        printError();
        return -1;   
    }


    client.sin_family = AF_INET;
    client.sin_port = htons( port );
    client.sin_addr.s_addr = inet_addr(ipAddr.c_str());


    //connect to client at ip ipAddr
    while(connect(clientSockFd, reinterpret_cast<sockaddr*>(&client), clientLen) == -1){
        
        if(errno != ECONNREFUSED){
            printError();
            return -1;
        }   
    }
        
    return 1;
}

int SocketHandle::initServer(){
    sockaddr_in server, acceptStruct;
    socklen_t serverLen = sizeof(sockaddr_in);

    serverSockFd = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSockFd == -1){
        printError();
        return -1;
    }
    
    //bind
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSockFd, reinterpret_cast<sockaddr*>(&server), serverLen) == -1){
        printError();
        return -1;
    }
    //listen
    if(listen(serverSockFd, 1) == -1){ //backlog is 1 only one client allowed
        printError();
        return -1;
    }
    //accept
    serverSendSockFd = accept(serverSockFd, reinterpret_cast<sockaddr*>(&acceptStruct), &serverLen);

    if(serverSendSockFd == -1){
        printError();
        return -1;
    }

    //check if person connected is correct
    if(inet_ntoa(acceptStruct.sin_addr) != ipAddr)
        return -1;
    
    
    std::cout<<"Connected to: "<<inet_ntoa(acceptStruct.sin_addr)<<std::endl;
    
    return 1;
}

std::string SocketHandle::recvData(){
    char buffer[2000];
    int dataLen;

    if( (dataLen = recv(clientSockFd, buffer, 2000, 0)) == -1){
        printError();
        return {};
    }

    return std::string(buffer, dataLen);
}

int SocketHandle::sendData(const std::string& data){
    unsigned int dataSent = 0, i = 0;
    const int timeout = 2000;

    while(dataSent != data.length()){
        dataSent = send(serverSendSockFd, data.c_str(), data.length(), 0);

        if(dataSent == -1 || i == timeout){
            printError();
            return -1;
        }

        i++;
    }

    return 1;
}

int SocketHandle::runP2PSocket(){
    //run client and server at the same time if error abort
    int result = 0;

    auto clientFuture = std::async(std::launch::async,
        [this, &result](){
            result |= initClient();
        }
    );
    
    result |= initServer();
    
    clientFuture.get();
    return result;
}

void SocketHandle::printError(){
    std::cerr<<"ERROR:"<<std::string(strerror(errno))<<std::endl;
    exit(1);
}

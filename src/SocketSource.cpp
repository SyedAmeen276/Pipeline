//SockerSource.cpp
#include "SocketSource.hpp"
#include "DataPacket.hpp"
#include<iostream>
#include<thread>
#include <unistd.h>
#include <arpa/inet.h>
#include<string>
#include <cstring> 
#include <cerrno>  

#define MAX_BUFFER_SIZE 1024

SocketSource::SocketSource(const std::string &host, int port)
    : m_host(host), m_port(port) {}

SocketSource::~SocketSource()
{
    StopReading();
}

void SocketSource::Run(PacketHandler handler)
{
    int sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockFd < 0) 
    {
        std::cerr << "failed to open the socket" << strerror(errno)  << std::endl;
        return;
    }

    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_host.c_str(), &servAddr.sin_addr); 

    if(connect(sockFd, (sockaddr*) &servAddr, sizeof(sockaddr_in)))
    {
        std::cerr << "failed to connect" << strerror(errno) << std::endl;
        close(sockFd);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (m_running)
    {
        ssize_t bytes = recv(sockFd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0)
            break;

        buffer[bytes] = '\0';
        auto packet = std::make_shared<DataPacket>(buffer, Name());
        handler(packet);
    }

    close(sockFd);

}

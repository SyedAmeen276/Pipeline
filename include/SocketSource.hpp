//SocketSource.hpp
#pragma once

#include "InputSource.hpp"
#include <thread>
#include <atomic>
#include <string>
#include <netinet/in.h>

class SocketSource : public InputSource
{
public:
    SocketSource(const std::string &host, int port);
    ~SocketSource();

    std::string Name() const override { return "SocketSource"; }

protected:
    void Run(PacketHandler handler) override;

private:
    std::string m_host;
    int m_port;
};

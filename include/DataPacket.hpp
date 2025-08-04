//DataPacket.hpp
#pragma once

#include<string>
#include<chrono>

struct DataPacket 
{
    std::string m_payload;
    std::chrono::steady_clock::time_point m_timeStamp;
    std::string m_source;

    DataPacket(const std::string &payload, const std::string &source) : m_payload(payload), m_timeStamp(std::chrono::steady_clock::now()), m_source(source) {}

};

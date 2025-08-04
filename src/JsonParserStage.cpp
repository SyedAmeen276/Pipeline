//JsonParserStage.cpp

#include "JsonParserStage.hpp"
#include <iostream>

std::shared_ptr<DataPacket> JsonParserStage::Process(std::shared_ptr<DataPacket> pkt)
{
    if (!pkt || pkt->m_payload.empty())
    {
        // std::cerr << "[JsonParserStage] Empty or null payload, skipping\n";
        return nullptr;
    }
    try
    {
        auto json = json::parse(pkt->m_payload);
        pkt->m_payload = json.dump();
        return pkt;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[JsonParserStage] Failed to parse JSON: " << e.what() << std::endl;
        return nullptr;
    }
}

JsonParserStage::~JsonParserStage()
{
}


//JsonParserStage.cpp

#include "JsonParserStage.hpp"
#include <iostream>
#include "Logger.hpp"

std::shared_ptr<DataPacket> JsonParserStage::Process(std::shared_ptr<DataPacket> pkt)
{
    if (!pkt || pkt->m_payload.empty())
    {
        Logger::get()->error("[JsonParseStage] Json Parse Error Empty or null Payload");
        return nullptr;
    }
    try
    {
        auto json = json::parse(pkt->m_payload);
        pkt->m_payload = json.dump();
        Logger::get()->info("[JsonParseStage] Json for Id {}", json["event_id"]);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return pkt;
    }
    catch (const std::exception &e)
    {
        Logger::get()->error("[JsonParseStage] Json Parse Error Failed to Parse {}", e.what());
        return nullptr;
    }
}



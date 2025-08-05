// FlinkStage.cpp
#include "FlinkStage.hpp"
#include <iostream>
#include <fstream>
#include "Logger.hpp"
#include<chrono>

std::shared_ptr<DataPacket> FlinkStage::Process(std::shared_ptr<DataPacket> pkt)
    {
    try
    {
       json jsonParsed = json::parse(pkt->m_payload);
       if (!jsonParsed.contains("event_id"))
       {
           Logger::get()->error("[FlinkStage] does not contain event_id null" );
           return nullptr;
       }

       std::string eventId = jsonParsed["event_id"];
       std::string sourceName = pkt->m_source.empty() ? "unknown" : pkt->m_source;

       std::string filename = sourceName + "_" + eventId + ".json";
       std::string filepath = filename;

       std::ofstream out(filepath);
       if (!out.is_open())
       {
           Logger::get()->error("[FlinkStage] Cannot open file {}", filepath);
           return nullptr;
       }
       auto now = std::chrono::steady_clock::now();
       auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(now - pkt->m_timeStamp).count();
       Logger::get()->info("[FlinkStage] Packet latency: {} ms", latency);

       out << jsonParsed.dump(2) << std::endl;
       Logger::get()->info("[FlinkStage] End of the stage {}", jsonParsed["event_id"]);
       out.close();
    }
    catch (const std::exception &e)
    {
        Logger::get()->error("[FlinkStage] Error writing packet {}", e.what());
    }

    return nullptr;
}



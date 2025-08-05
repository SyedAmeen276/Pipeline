// FlinkStage.cpp
#include "FlinkStage.hpp"
#include <iostream>
#include <fstream>

std::shared_ptr<DataPacket> FlinkStage::Process(std::shared_ptr<DataPacket> pkt)
    {
    try
    {
       json jsonParsed = json::parse(pkt->m_payload);
       if (!jsonParsed.contains("event_id"))
       {
           std::cerr << "[FileSinkStage] Missing 'event_id' in payload\n";
           return nullptr;
       }

       std::string eventId = jsonParsed["event_id"];
       std::string sourceName = pkt->m_source.empty() ? "unknown" : pkt->m_source;

       std::string filename = sourceName + "_" + eventId + ".json";
       std::string filepath = filename;

       std::ofstream out(filepath);
       if (!out.is_open())
       {
           std::cerr << "[FileSinkStage] Cannot open file: " << filepath << "\n";
           return nullptr;
       }
       
       out << jsonParsed.dump(2) << std::endl;
       out.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[FileSinkStage] Error writing packet: " << e.what() << "\n";
    }

    return nullptr;
}



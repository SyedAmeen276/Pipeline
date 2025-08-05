//FilterStage.cpp
#include "FilterStage.hpp"
#include <iostream>
#include "Logger.hpp"

std::shared_ptr<DataPacket> FilterStage::Process(std::shared_ptr<DataPacket> pkt) 
{
    auto json = json::parse(pkt->m_payload, nullptr, false);
    if (!json.contains("metadata") || !json["metadata"].contains("priority"))
    {
        Logger::get()->error("[FilterStage] Missing priority field from Metadata");
        return nullptr;
    }

    int priority = json["metadata"]["priority"];
    if (priority < 3)
    {
        Logger::get()->warn("[FilterStage] Dropping low-priority event");
        return nullptr;
    }

    Logger::get()->info("[FilterStage] Json for Id {}", json["event_id"]);
    return pkt;
}

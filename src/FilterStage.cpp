//FilterStage.cpp
#include "FilterStage.hpp"
#include <iostream>


std::shared_ptr<DataPacket> FilterStage::Process(std::shared_ptr<DataPacket> pkt) 
{
    auto json = json::parse(pkt->m_payload, nullptr, false);
    if (!json.contains("metadata") || !json["metadata"].contains("priority"))
    {
        std::cerr << "[FilterStage] Missing priority field." << std::endl;
        return nullptr;
    }

    int priority = json["metadata"]["priority"];
    if (priority < 3)
    {
        std::cerr << "[FilterStage] Dropping low-priority event." << std::endl;
        return nullptr;
    }

    return pkt;
}

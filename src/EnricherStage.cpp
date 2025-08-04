//EnricherStage.cpp
#include "EnricherStage.hpp"
#include<iostream>
#include <chrono>

std::shared_ptr<DataPacket> EnricherStage::Process(std::shared_ptr<DataPacket> pkt)
{
    auto json = json::parse(pkt->m_payload);

    if (json.contains("payload") && json["payload"].contains("temperature"))
    {
        double temp = json["payload"]["temperature"];
        json["payload"]["temperature_alert"] = (temp > 30.0);
    }

    pkt->m_payload = json.dump();
    return pkt;
}

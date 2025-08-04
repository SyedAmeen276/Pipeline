// TransFormStage.cpp
#include "TransformStage.hpp"
#include <nlohmann/json.hpp>
#include<iostream>

std::shared_ptr<DataPacket> TransformStage::Process(std::shared_ptr<DataPacket> pkt)
{
    auto jsonParsed = json::parse(pkt->m_payload);

    json flat;
    std::cout << "[Success] TransformStage start JSON:\n"
              << jsonParsed.dump(2) << std::endl;
    flat["event_id"] = jsonParsed["event_id"];
    flat["event_type"] = jsonParsed["type"];
    flat["temperature"] = jsonParsed["payload"]["temperature"];
    flat["humidity"] = jsonParsed["payload"]["humidity"];
    flat["alert"] = jsonParsed["payload"]["temperature_alert"];
    flat["location"] = jsonParsed["metadata"]["location"];
    flat["priority"] = jsonParsed["metadata"]["priority"];

    pkt->m_payload = flat.dump(2);
    return pkt;
}

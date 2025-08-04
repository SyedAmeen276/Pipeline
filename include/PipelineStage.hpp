//PipelineStage.hpp
#pragma once

#include "DataPacket.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class PipelineStage 
{
public:
    virtual ~PipelineStage() = default;

    virtual std::shared_ptr<DataPacket> Process(std::shared_ptr<DataPacket> pkt) = 0;

    virtual void Initalize() {};
    virtual void Shutdown() {};
};

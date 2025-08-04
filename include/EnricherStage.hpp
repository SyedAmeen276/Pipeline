//EnricherStage.hpp
#pragma once

#include "PipelineStage.hpp"
#include <memory>

class EnricherStage : public PipelineStage
{
public:
    std::shared_ptr<DataPacket> Process(std::shared_ptr<DataPacket> pkt) override;
};

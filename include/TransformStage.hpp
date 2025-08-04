//TransformStage.hpp
#pragma once

#include "PipelineStage.hpp"
#include <memory>

class TransformStage : public PipelineStage
{
public:
    std::shared_ptr<DataPacket> Process(std::shared_ptr<DataPacket> pkt) override;
};

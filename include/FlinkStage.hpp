//FlinkStage.hpp
#pragma once

#include "PipelineStage.hpp"
#include <memory>

class FlinkStage : public PipelineStage
{
public:
    std::shared_ptr<DataPacket> Process(std::shared_ptr<DataPacket> pkt) override;

private:
    std::string m_outputDir = "output";
};

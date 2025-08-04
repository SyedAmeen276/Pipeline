//JsonPraserStage.hpp
#pragma once

#include "PipelineStage.hpp"
#include <memory>

class JsonParserStage : public PipelineStage
{
public:
    ~JsonParserStage();
    std::shared_ptr<DataPacket> Process(std::shared_ptr<DataPacket> pkt) override;
};

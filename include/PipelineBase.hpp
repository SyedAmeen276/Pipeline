//PipelineBase.hpp
#pragma once

#include "PipelineStage.hpp"
#include <memory>

class PipelineBase
{
public:
    ~PipelineBase() = default;

    virtual void AddStage(std::shared_ptr<PipelineStage> stage) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Push(std::shared_ptr<DataPacket> pkt) = 0;

};




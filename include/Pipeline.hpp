//Pipeline.hpp
#pragma once

#include "PipelineBase.hpp"
#include<vector>
#include<thread>
#include<atomic>
#include <boost/lockfree/spsc_queue.hpp>

class Pipeline: public PipelineBase
{
public:
    Pipeline();
    ~Pipeline();

    void AddStage(std::shared_ptr<PipelineStage> stage) override;
    void Start() override;
    void Stop() override;
    void Push(std::shared_ptr<DataPacket> pkt) override;

private:
    using Queue = boost::lockfree::spsc_queue<std::shared_ptr<DataPacket>>;
    std::vector<std::shared_ptr<Queue>> m_queue;

    std::vector<std::shared_ptr<PipelineStage>> m_stages;
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_running;
};



#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include "PipelineStage.hpp"
#include "DataPacket.hpp"
#include "ThreadSafeQueue.hpp"

class Pipeline
{
public:
    using PacketPtr = std::shared_ptr<DataPacket>;

    Pipeline();
    ~Pipeline();

    void AddStage(std::shared_ptr<PipelineStage> stage, size_t numThreads = 1);
    void Start();
    void Stop();
    void Push(PacketPtr pkt);

private:
    struct StageContext
    {
        std::shared_ptr<PipelineStage> stage;
        std::shared_ptr<ThreadSafeQueue<PacketPtr>> inputQueue;
        std::shared_ptr<ThreadSafeQueue<PacketPtr>> outputQueue;
        std::vector<std::thread> workers;
        size_t numThreads = 1;
    };

    std::vector<StageContext> m_stages;
    std::atomic<bool> m_running;
};

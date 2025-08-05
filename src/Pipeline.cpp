#include "Pipeline.hpp"
#include <iostream>

Pipeline::Pipeline() : m_running(false) {}

Pipeline::~Pipeline()
{
    Stop();
}

void Pipeline::AddStage(std::shared_ptr<PipelineStage> stage, size_t numThreads)
{
    StageContext ctx;
    ctx.stage = stage;
    ctx.inputQueue = std::make_shared<ThreadSafeQueue<PacketPtr>>();
    ctx.outputQueue = nullptr;
    ctx.numThreads = numThreads;
    m_stages.push_back(std::move(ctx));
}

void Pipeline::Start()
{
    if (m_stages.empty())
        return;

    for (size_t i = 0; i + 1 < m_stages.size(); ++i)
    {
        m_stages[i].outputQueue = m_stages[i + 1].inputQueue;
    }

    m_running = true;

    for (auto &ctx : m_stages)
    {
        ctx.stage->Initalize();

        for (size_t i = 0; i < ctx.numThreads; ++i)
        {
            ctx.workers.emplace_back([this, &ctx]()
                                     {
                while (m_running)
                {
                    PacketPtr pkt;
                    ctx.inputQueue->wait_and_pop(pkt);

                    if (!pkt)
                        continue;

                    auto result = ctx.stage->Process(pkt);

                    if (result && ctx.outputQueue)
                    {
                        ctx.outputQueue->push(result);
                    }
                } });
        }
    }
}

void Pipeline::Stop()
{
    m_running = false;

    for (auto &ctx : m_stages)
    {
        for (size_t i = 0; i < ctx.numThreads; ++i)
            ctx.inputQueue->push(nullptr);

        for (auto &t : ctx.workers)
        {
            if (t.joinable())
                t.join();
        }
        ctx.workers.clear();

        ctx.stage->Shutdown();
    }
}

void Pipeline::Push(PacketPtr pkt)
{
    if (!m_stages.empty())
    {
        m_stages.front().inputQueue->push(pkt);
    }
}

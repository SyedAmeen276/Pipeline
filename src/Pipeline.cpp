//Pipeline.cpp
#include "Pipeline.hpp"

Pipeline::Pipeline() : m_running(false) {};

Pipeline::~Pipeline()
{
    Stop();
}

void Pipeline::AddStage(std::shared_ptr<PipelineStage> stage)
{
    m_stages.push_back(stage);
}

void Pipeline::Start()
{
    if (m_stages.empty())
        return;

    m_running = true;

    m_queue.resize(m_stages.size() - 1);
    for (auto &q : m_queue)
    {
        q = std::make_shared<Queue>(1024);
    }

    for (size_t i = 0; i < m_stages.size(); ++i)
    {
        auto inputQueue = (i == 0) ? nullptr : m_queue[i - 1];
        auto outputQueue = (i == m_stages.size() - 1) ? nullptr : m_queue[i];

        m_threads.emplace_back([this, stage = m_stages[i], inputQueue, outputQueue]()
                              {
            stage->Initalize();

            while (m_running) {
                std::shared_ptr<DataPacket> pkt;

                if (inputQueue) {
                    if (!inputQueue->pop(pkt)) {
                        std::this_thread::yield();
                        continue;
                    }
                }

                auto result = stage->Process(pkt);
                if (result && outputQueue) {
                    while (!outputQueue->push(result)) {
                        std::this_thread::yield();
                    }
                }
            }

            stage->Shutdown(); 
        });
    }
}

void Pipeline::Stop()
{
    m_running = false;

    for (auto &t : m_threads)
    {
        if (t.joinable())
            t.join();
    }

    m_threads.clear();
    m_queue.clear();
}

void Pipeline::Push(std::shared_ptr<DataPacket> pkt)
{
    if (!m_queue.empty() && m_queue[0])
    {
        while (!m_queue[0]->push(pkt))
        {
            std::this_thread::yield();
        }
    }
}

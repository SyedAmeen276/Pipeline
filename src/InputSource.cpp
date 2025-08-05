// InputSource.cpp

#include "InputSource.hpp"
#include <iostream>

void InputSource::StartReading(PacketHandler handler)
{
    if (m_running)
        return; // already running return
    m_running = true;
    m_worker = std::thread([this, handler](){
        Run(handler); 
    });
}

InputSource::~InputSource() = default;

void InputSource::StopReading()
{
    if (m_running)
    {
        m_running = false;
        if (m_worker.joinable())
        {
            m_worker.join();
        }
    }
}

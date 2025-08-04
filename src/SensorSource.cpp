// SenesorSource.cpp
#include "SensorSource.hpp"
#include "DataPacket.hpp"
#include <iostream>
#include <random>


SensorSource::SensorSource(int interval_ms)
    : m_IntervalMs(interval_ms)  {}

SensorSource:: ~SensorSource()
{
    StopReading();
}

void SensorSource::Run(PacketHandler handler)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> temp(20, 40);

    while (m_running)
    {
        int t = temp(gen);
        auto packet = std::make_shared<DataPacket>("temperature=" + std::to_string(t), Name());
        handler(packet);
        std::this_thread::sleep_for(std::chrono::milliseconds(m_IntervalMs));
    }
}
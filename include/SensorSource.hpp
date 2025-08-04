// SensorSource.hpp
#pragma once

#include "InputSource.hpp"
#include <string>
#include <thread>
#include <atomic>

class SensorSource : public InputSource
{
public:
    explicit SensorSource(int interval_ms);
    ~SensorSource() override;

    std::string Name() const override { return "SensorSource"; }

protected:
    void Run(PacketHandler handler) override;

private:
    int m_IntervalMs;
};

// InputSource.hpp
#pragma once

#include <functional>
#include <atomic>
#include <thread>
#include <memory>
#include <string>

class DataPacket; // forward declaration

class InputSource
{
public:
    using PacketHandler = std::function<void(std::shared_ptr<DataPacket>)>;

    virtual ~InputSource();

    // Start reading from source
    virtual void StartReading(PacketHandler handler);

    // Stop the source gracefully
    virtual void StopReading();

    // Name or ID for logging/metrics
    virtual std::string Name() const = 0;

protected:
    virtual void Run(PacketHandler handler) = 0; 

    std::atomic<bool> m_running{false};
    std::thread m_worker;
};

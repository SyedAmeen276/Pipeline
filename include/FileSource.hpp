//FileSource.hpp
#pragma once

#include "InputSource.hpp"
#include <string>
#include <thread>
#include <atomic>

class FileSource : public InputSource 
{
public:
    explicit FileSource(const std::string &filePath);
    ~FileSource() override;

    std::string Name() const override { return "FileTailSource"; }

protected:
    void Run(PacketHandler handler) override;

private:
    std::string m_filePath;
};

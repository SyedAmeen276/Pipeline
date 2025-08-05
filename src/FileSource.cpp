//FileSource.cpp
#include "FileSource.hpp"
#include "DataPacket.hpp"
#include<iostream>
#include <fstream>
#include<thread>
#include<chrono>
#include <nlohmann/json.hpp>
#include "Logger.hpp"

using json = nlohmann::json;
FileSource::FileSource(const std::string &filepath) : m_filePath (filepath) {}

FileSource::~FileSource()
{
    StopReading();
}

void FileSource::Run(PacketHandler handler)
{
    std::ifstream file(m_filePath);
    if (!file)
    {
        Logger::get()->error("Failed to open file:{}", m_filePath);
        return;
    }

    std::string line;
    std::string buffer;
    
    while (m_running)
    {
        std::streampos current_pos = file.tellg();

        if (std::getline(file, line))
        {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            if (line.empty())
                continue;

            buffer += line + "\n";

            try
            {
                json parsed = json::parse(buffer);

                auto pkt = std::make_shared<DataPacket>(parsed.dump(), Name());
                Logger::get()->info("Created a pkt and passing to First Stage of Pipeline");
                handler(pkt);

                buffer.clear();
            }
            catch (const json::parse_error &e)
            {
               
            }
        }
        else
        {
            file.clear(); 
            file.seekg(current_pos);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    if (!buffer.empty())
    {
        Logger::get()->error("Unparsed leftover data {}", buffer);
    }
}
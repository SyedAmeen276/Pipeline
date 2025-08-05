#include "Pipeline.hpp"
#include "FileSource.hpp"
#include "JsonParserStage.hpp"
#include "FilterStage.hpp"
#include "EnricherStage.hpp"
#include "TransformStage.hpp"
#include "FlinkStage.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <csignal>

std::vector<std::unique_ptr<FileSource>> sources;
std::unique_ptr<Pipeline> pipeline;

void SignalHandler(int signum)
{
    std::cout << "\n[Main] Caught signal " << signum << ", shutting down..." << std::endl;

    for (auto &src : sources)
        src->StopReading();

    if (pipeline)
        pipeline->Stop();

    std::exit(signum);
}

int main()
{
    std::signal(SIGINT, SignalHandler);

    pipeline = std::make_unique<Pipeline>();

    pipeline->AddStage(std::make_shared<JsonParserStage>(), 3);
    pipeline->AddStage(std::make_shared<FilterStage>(), 3);
    pipeline->AddStage(std::make_shared<EnricherStage>(), 3);
    pipeline->AddStage(std::make_shared<TransformStage>(), 3);
    pipeline->AddStage(std::make_shared<FlinkStage>(), 3);

    pipeline->Start();

    std::vector<std::string> files = {"input1.txt", "input2.txt", "input.txt"};

    for (const auto &file : files)
    {
        auto src = std::make_unique<FileSource>(file);

        src->StartReading([&](std::shared_ptr<DataPacket> pkt)
                          { pipeline->Push(pkt); });

        sources.push_back(std::move(src));
    }

    std::cout << "[Main] Running. Press Ctrl+C to exit...\n";

    while (true)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}

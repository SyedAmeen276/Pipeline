#include "FileSource.hpp"
#include "Pipeline.hpp"
#include "JsonParserStage.hpp"
#include "FilterStage.hpp"
#include "EnricherStage.hpp"
#include "TransformStage.hpp"
#include "FlinkStage.hpp"

#include <iostream>
#include <memory>
#include <csignal>

std::unique_ptr<FileSource> fileSource;
std::unique_ptr<Pipeline> pipeline;

void SignalHandler(int signum)
{
    std::cout << "\n[Main] Caught signal " << signum << ", shutting down..." << std::endl;
    if (fileSource)
        fileSource->StopReading();
    if (pipeline)
        pipeline->Stop();
    std::exit(signum);
}

void check()
{
    std::cout << "check" << std::endl;
}

int main()
{
    std::signal(SIGINT, SignalHandler);

    // Create input source
    fileSource = std::make_unique<FileSource>("input.txt");

    // Create and configure pipeline
    pipeline = std::make_unique<Pipeline>();
    pipeline->AddStage(std::make_shared<JsonParserStage>());
    pipeline->AddStage(std::make_shared<FilterStage>());
    pipeline->AddStage(std::make_shared<EnricherStage>());
    pipeline->AddStage(std::make_shared<TransformStage>());
    pipeline->AddStage(std::make_shared<FlinkStage>());

    // Start pipeline
    pipeline->Start();

    // Start reading from file and pushing into pipeline
    fileSource->StartReading([&](std::shared_ptr<DataPacket> pkt)
                             { pipeline->Push(pkt); });

    // Block until Ctrl+C
    // std::cout << "[Main] Pipeline and FileSource running. Press Ctrl+C to stop..." << std::endl;
    while (true)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
//Logger.hpp
#pragma once

#include <memory>
#include <string>
#include <spdlog/spdlog.h>

class Logger
{
public:
    static std::shared_ptr<spdlog::logger> &get();

    static void Init(const std::string &filename = "pipeline.log");

private:
    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

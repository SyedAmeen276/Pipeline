#include "Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> &Logger::get()
{
    static std::shared_ptr<spdlog::logger> instance = nullptr;
    return instance;
}

void Logger::Init(const std::string &filename)
{
    if (!get())
    {
        try
        {
            std::vector<spdlog::sink_ptr> sinks;

            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::info);
            sinks.push_back(console_sink);

            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
            file_sink->set_level(spdlog::level::debug);
            sinks.push_back(file_sink);

            get() = std::make_shared<spdlog::logger>("pipeline_logger", begin(sinks), end(sinks));
            get()->set_level(spdlog::level::debug);
            get()->flush_on(spdlog::level::info);

            get()->info("Logger initialized. Writing to console and {}", filename);
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            // Fallback: write to stderr
            fprintf(stderr, "Logger initialization failed: %s\n", ex.what());
        }
    }
}

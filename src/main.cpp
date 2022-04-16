#include "Server/servermanager.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"


int main(void) {

    { // SPDLOG config
        const std::string path = "./server.log";

            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path, true);

            spdlog::set_default_logger(std::make_shared<spdlog::logger>(
                "default", spdlog::sinks_init_list{console_sink, file_sink}));
        #if (SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG)
            spdlog::flush_on(spdlog::level::debug);
            spdlog::set_level(spdlog::level::debug);
        #elif (SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO)
            spdlog::flush_on(spdlog::level::info);
            spdlog::set_level(spdlog::level::info);
        #endif
            SPDLOG_DEBUG("Logging setted.");
    }
    ServerManager::GetInstance()->ScanController();

    ServerManager::GetInstance()->Start();

    ServerManager::GetInstance()->Exec();

    SPDLOG_INFO("🛫Bye");
    return 0;
}

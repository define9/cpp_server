#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <httplib.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include "src/controller/controller.hpp"
#include "src/controller/democontroller.hpp"

#include <vector>

class ServerManager
{
private:

    static ServerManager *server_manager_;
    std::shared_ptr<httplib::Server> server_ = nullptr;

    // 维护 Controller
    std::vector<std::shared_ptr<Controller>> controllers_;

    std::thread server_thread_;

    ServerManager();

public:
    ~ServerManager();
    static ServerManager* GetInstance();

    void Work();

    void ScanController();

    int Start(int port = 80, const std::string &staticPath = "www");

    void Stop();
};

#endif // SERVERMANAGER_HPP

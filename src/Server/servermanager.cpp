#include "servermanager.hpp"

ServerManager* ServerManager::server_manager_ = new ServerManager;

ServerManager::ServerManager()
{
    server_ = std::make_shared<httplib::Server>();
}

ServerManager::~ServerManager()
{
    if (server_->is_running())
        this->Stop();
}

ServerManager *ServerManager::GetInstance()
{
    return server_manager_;
}

void ServerManager::Work()
{
    server_->listen_after_bind();
    SPDLOG_WARN("The Server Stop listen");
}

void ServerManager::ScanController()
{
    // 注册 Controller
    controllers_.push_back(std::make_shared<DemoController>());
    controllers_.push_back(std::make_shared<AdminController>());

    SPDLOG_INFO("Contorller size: {}", controllers_.size());

    // 执行Route 扫描 method，无需改动
    for (uint8_t i = 0; i < controllers_.size(); i ++) {
        controllers_[i]->Route(server_);
    }
}

int ServerManager::Start(int port, const std::string &staticPath)
{
    if (server_->is_running()) {
        SPDLOG_WARN("The server is already running");
        return 1;
    }

    if (!server_->is_valid()) {
        SPDLOG_ERROR("The port is not valid");
        return 2;
    }

    if (!server_->bind_to_port("127.0.0.1", port) ) {
        SPDLOG_ERROR("The server failed to run on port {}, Please check the port", port);
        return -1;
    }

    if (staticPath.length() > 0) {
        server_->set_base_dir(staticPath);
    }

    server_thread_ = std::thread(&ServerManager::Work, this);
    SPDLOG_INFO("The server success to run on port {}", port);
    SPDLOG_INFO("your url: http://127.0.0.1:{}", port);
    return 0;
}

void ServerManager::Stop()
{
    SPDLOG_INFO("Call stop function");
    if (!server_->is_running()) {
        SPDLOG_INFO("The Server already Stop");
        return;
    }
    server_->stop();
    server_thread_.join();
    SPDLOG_INFO("The server has stopped");
}

void ServerManager::Exec()
{
    SPDLOG_INFO("🐌The server is running in blocking mode");
    server_thread_.join();
}

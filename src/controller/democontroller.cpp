#include "democontroller.hpp"


DemoController::DemoController()
{

}

DemoController::~DemoController()
{

}

void DemoController::Route(std::shared_ptr<httplib::Server> server_ptr)
{
    server_ptr->Get("/hi", &DemoController::Demo);

    SPDLOG_INFO("add Route");
}

void DemoController::Demo(const httplib::Request &req, httplib::Response &res)
{
    res.set_content("hi", "text/html");
}

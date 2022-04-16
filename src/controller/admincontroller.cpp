#include "admincontroller.hpp"

AdminController::AdminController()
{

}

void AdminController::Route(std::shared_ptr<httplib::Server> server_ptr)
{
    server_ptr->Get(prefix + "/stop", [=](const httplib::Request &req, httplib::Response &res){
        res.set_content("🎁The Server will stop🖐", "text/html; charset=utf-8");
        server_ptr->stop();
    });
}

#include "democontroller.hpp"


DemoController::DemoController()
{

}

DemoController::~DemoController()
{

}

void DemoController::Route(std::shared_ptr<httplib::Server> server_ptr)
{
    server_ptr->Get(Prefix + "/test", &DemoController::Demo);
}

void DemoController::Demo(const httplib::Request &req, httplib::Response &res)
{
    Json::Value r;
    if (!req.has_param("name")) {
        r["content"] = "errorwww";
        res.set_content(r.toStyledString(), DataFormat::kJSON.c_str());
    }
    else {
        r["content"] = "succ";
        res.set_content(r.toStyledString(), DataFormat::kJSON.c_str());
    }
}

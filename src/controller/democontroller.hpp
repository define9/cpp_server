#ifndef DEMOCONTROLLER_HPP
#define DEMOCONTROLLER_HPP

#include "src/controller/controller.hpp"

class DemoController : public Controller
{
private:
    std::string Prefix = "/api/test_1";
public:
    DemoController();

    ~DemoController();

    void Route(std::shared_ptr<httplib::Server>) override;

    void static Demo(const httplib::Request &req, httplib::Response &res);
};

#endif // DEMOCONTROLLER_HPP

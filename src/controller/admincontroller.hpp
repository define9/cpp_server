#ifndef ADMINCONTROLLER_HPP
#define ADMINCONTROLLER_HPP

#include "src/controller/controller.hpp"
#include "src/utils/util.hpp"

class AdminController : public Controller
{
private:
    std::string prefix = "/admin";

public:
    AdminController();

    void Route(std::shared_ptr<httplib::Server>) override;
};

#endif // ADMINCONTROLLER_HPP

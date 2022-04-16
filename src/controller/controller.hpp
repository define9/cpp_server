#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "httplib.hpp"
#include <spdlog/spdlog.h>

class Controller {
public:
    virtual void Route(std::shared_ptr<httplib::Server>) = 0;
};

#endif // CONTROLLER_HPP

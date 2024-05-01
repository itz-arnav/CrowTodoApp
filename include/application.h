#pragma once
#include "controller.h"
#include <stdexcept>
#include <string>

class Application {
public:
    Application();
    void run();
private:
    Controller *m_controller;
};

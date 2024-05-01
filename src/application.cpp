#include "../include/application.h"

Application::Application() {
    try {
        m_controller = new Controller();
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Error in setting up the Controller: ") + e.what());
    }
}

void Application::run() {
    try {
        m_controller->setupRoutes();
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Error in setting up the routes: ") + e.what());
    }
}

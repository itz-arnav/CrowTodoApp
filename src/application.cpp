#include "../include/application.h"

Application::Application() {
    try {
        m_controller = new Controller();
        std::cout << "Successfully setup the server on port 7777" << std::endl;
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

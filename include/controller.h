#pragma once
#include <memory>
#include <crow.h>
#include <crow/middlewares/cors.h>
#include "database.h"
#include "db_constants.h"

class Controller {
public:
    Controller();
    ~Controller();
    void setupRoutes();

private:
    std::unique_ptr<Database> database;
    crow::App<crow::CORSHandler> app;

    void createItem(const crow::request& req, crow::response& res);
    void readAllItems(crow::response& res);
    void readItem(const crow::request& req, crow::response& res, const std::string& id);
    void updateItem(const crow::request& req, crow::response& res);
    void deleteItem(const crow::request& req, crow::response& res, const std::string& id);
};

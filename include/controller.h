#pragma once
#include <memory>
#include "database.h"
#include <crow.h>
#include "db_constants.h"

class Controller {
public:
    Controller();
    ~Controller();
    void setupRoutes();

private:
    std::unique_ptr<Database> database;
    crow::SimpleApp app;

    void createItem(const crow::request& req, crow::response& res);
    void readAllItems(crow::response& res);
    void readItem(const crow::request& req, crow::response& res, const std::string& id);
    void updateItem(const crow::request& req, crow::response& res);
    void deleteItem(const crow::request& req, crow::response& res, const std::string& id);
};

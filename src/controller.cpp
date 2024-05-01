#include "../include/controller.h"

Controller::Controller() : database(std::make_unique<Database>("todoappdemo.db")) {}

Controller::~Controller() {}

void Controller::setupRoutes() {
    CROW_ROUTE(app, "/item/all").methods(crow::HTTPMethod::Get)([this](const crow::request& req, crow::response& res) {
        try {
            readAllItems(res);
        } catch (const std::exception& e) {
            res.code = 500;
            res.end("Internal server error: " + std::string(e.what()));
        }
    });

    CROW_ROUTE(app, "/item/create").methods(crow::HTTPMethod::Post)([this](const crow::request& req, crow::response& res) {
        try {
            createItem(req, res);
        } catch (const std::exception& e) {
            res.code = 500;
            res.end("Internal server error: " + std::string(e.what()));
        }
    });

    CROW_ROUTE(app, "/item/read/<string>").methods(crow::HTTPMethod::Get)([this](const crow::request& req, crow::response& res, const std::string& id) {
        try {
            readItem(req, res, id);
        } catch (const std::exception& e) {
            res.code = 500;
            res.end("Internal server error: " + std::string(e.what()));
        }
    });

    CROW_ROUTE(app, "/item/update").methods(crow::HTTPMethod::Put)([this](const crow::request& req, crow::response& res) {
        try {
            updateItem(req, res);
        } catch (const std::exception& e) {
            res.code = 500;
            res.end("Internal server error: " + std::string(e.what()));
        }
    });

    CROW_ROUTE(app, "/item/delete/<string>").methods(crow::HTTPMethod::Delete)([this](const crow::request& req, crow::response& res, const std::string& id) {
        try {
            deleteItem(req, res, id);
        } catch (const std::exception& e) {
            res.code = 500;
            res.end("Internal server error: " + std::string(e.what()));
        }
    });

    app.port(7777).multithreaded().run();
}

void Controller::createItem(const crow::request& req, crow::response& res) {
    auto itemJson = crow::json::load(req.body);
    if (!itemJson) {
        res.code = 400;
        res.end("Invalid JSON");
        return;
    }

    std::string description = itemJson["description"].s();
    if (description.empty()) {
        res.code = 400;
        res.end("Missing fields");
        return;
    }

    Item newItem(description, ItemStatus::ITEM_NEW, false);
    bool success = database->createItem(newItem);
    if (success) {
        res.code = 201;
        res.end("Item created successfully");
    } else {
        res.code = 500;
        res.end("Failed to create item");
    }
}

void Controller::readAllItems(crow::response &res) {
    auto items = database->readAllItems();
    crow::json::wvalue responseJson;
    responseJson["items"] = std::vector<crow::json::wvalue>();
    for (size_t index = 0; index < items.size(); index++) {
        crow::json::wvalue itemJson;
        itemJson["uuid"] = items[index]->getUuid();
        itemJson["description"] = items[index]->getDescription();
        itemJson["status"] = static_cast<int>(items[index]->getItemStatus());
        itemJson["favourite"] = items[index]->isFavourite();
        responseJson["items"][index] = std::move(itemJson);
    }

    res.code = 200;
    res.write(responseJson.dump());
    res.end();
}

void Controller::readItem(const crow::request& req, crow::response& res, const std::string& id) {
    auto item = database->readItem(id);
    if (item) {
        crow::json::wvalue responseJson;
        responseJson["description"] = item->getDescription();
        responseJson["status"] = static_cast<int>(item->getItemStatus());
        responseJson["favourite"] = item->isFavourite();
        res.code = 200;
        res.write(responseJson.dump());
        res.end();
    } else {
        res.code = 404;
        res.end("Item not found");
    }
}

void Controller::updateItem(const crow::request& req, crow::response& res) {
    auto updateJson = crow::json::load(req.body);
    if (!updateJson) {
        res.code = 400;
        res.end("Invalid JSON");
        return;
    }

    if (!updateJson.has("uuid") || !updateJson.has("description") || !updateJson.has("status") || !updateJson.has("favourite")) {
        res.code = 400;
        res.end("Missing required fields: 'uuid', 'description', 'status', and 'favourite'");
        return;
    }

    std::string uuid = updateJson["uuid"].s();
    std::string description = updateJson["description"].s();
    int64_t status = updateJson["status"].i();
    bool favourite = updateJson["favourite"].b();

    Item updatedItem(uuid, description, static_cast<ItemStatus>(status), favourite);
    bool success = database->updateItem(updatedItem);

    if (success) {
        res.code = 200;
        res.end("Item updated successfully");
    } else {
        res.code = 500;
        res.end("Failed to update item");
    }
}

void Controller::deleteItem(const crow::request& req, crow::response& res, const std::string& id) {
    bool success = database->deleteItem(id);
    if (success) {
        res.code = 204;
        res.end();
    } else {
        res.code = 500;
        res.end("Failed to delete item");
    }
}

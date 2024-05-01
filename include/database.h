#pragma once
#include <memory>
#include "model.h"
#include <sqlite3.h>
#include <stdexcept>

class Database {
public:
    Database(const std::string& dbName = "todoappdemo.db");
    ~Database();

    void checkSqlResult(int rc, const char* contextMessage);
    bool createItem(const Item& item);
    std::vector<std::unique_ptr<Item>> readAllItems();
    std::unique_ptr<Item> readItem(const std::string& description);
    bool updateItem(const Item& newItem);
    bool deleteItem(const std::string& description);

private:
    sqlite3* db;
};

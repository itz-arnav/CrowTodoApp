#include "../include/database.h"

Database::Database(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        throw std::runtime_error("Failed to open the database: " + std::string(sqlite3_errmsg(db)));
    }

    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Items ("
                                 "UUID TEXT PRIMARY KEY, "
                                 "Description TEXT, "
                                 "Status INT, "
                                 "Favourite INT)";

    checkSqlResult(sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, nullptr), "Create table");
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::checkSqlResult(int rc, const char* contextMessage) {
    if (rc != SQLITE_OK) {
        std::string errMsg = sqlite3_errmsg(db);
        throw std::runtime_error(std::string(contextMessage) + ": " + errMsg);
    }
}

bool Database::createItem(const Item& item) {
    const char* sqlInsert = "INSERT INTO Items (UUID, Description, Status, Favourite) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, item.getUuid().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, item.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, static_cast<int>(item.getItemStatus()));
    sqlite3_bind_int(stmt, 4, static_cast<int>(item.isFavourite()));
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

std::vector<std::unique_ptr<Item> > Database::readAllItems()
{
    const char* sqlSelectAll = "SELECT UUID, Description, Status, Favourite FROM Items";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sqlSelectAll, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare read all items statement: " + std::string(sqlite3_errmsg(db)));
    }

    std::vector<std::unique_ptr<Item>> items;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string uuid = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        ItemStatus status = static_cast<ItemStatus>(sqlite3_column_int(stmt, 2));
        bool favourite = static_cast<bool> (sqlite3_column_int(stmt, 3));
        items.emplace_back(std::make_unique<Item>(description, status, favourite));
    }
    sqlite3_finalize(stmt);
    return items;
}

std::unique_ptr<Item> Database::readItem(const std::string& uuid) {
    const char* sqlSelect = "SELECT UUID, Description, Status, Favourite FROM Items WHERE UUID = ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, uuid.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string uuid = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string desc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        ItemStatus status = static_cast<ItemStatus>(sqlite3_column_int(stmt, 2));
        bool favourite = static_cast<bool>(sqlite3_column_text(stmt, 3));
        sqlite3_finalize(stmt);
        return std::make_unique<Item>(desc, status, favourite);
    }
    sqlite3_finalize(stmt);
    return nullptr;
}

bool Database::updateItem(const Item& newItem) {
    const char* sqlUpdate = "UPDATE Items SET Description = ?, Status = ?, Favourite = ? WHERE UUID = ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, newItem.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, static_cast<int>(newItem.getItemStatus()));
    sqlite3_bind_int(stmt, 3, static_cast<int>(newItem.isFavourite()));
    sqlite3_bind_text(stmt, 4, newItem.getUuid().c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}


bool Database::deleteItem(const std::string& uuid) {
    const char* sqlDelete = "DELETE FROM Items WHERE UUID = ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, uuid.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}


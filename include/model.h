#pragma once
#include "db_constants.h"
#include <string>
#include <SDKDDKVer.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>

class Item {
public:
    Item(const std::string& description, const ItemStatus& itemStatus, const bool& favourite);
    Item(const std::string& uuid, const std::string& description, const ItemStatus& itemStatus, const bool& favourite);

    std::string getDescription() const;
    ItemStatus getItemStatus() const;
    void setDescription(const std::string& newDescription);
    void setItemStatus(const ItemStatus& newItemStatus);
    std::string getUuid() const;
    bool isFavourite() const;
    void setFavourite(bool new_favourite);

private:
    std::string m_description;
    ItemStatus m_itemStatus;
    boost::uuids::uuid m_uuid;
    bool m_favourite;
};

#include "../include/model.h"

Item::Item(const std::string& description, const ItemStatus& itemStatus, const bool& favourite)
    : m_description(description), m_itemStatus(itemStatus), m_favourite(favourite), m_uuid(boost::uuids::random_generator()()) {
}

Item::Item(const std::string &uuid, const std::string &description, const ItemStatus &itemStatus, const bool &favourite)
    : m_description(description), m_itemStatus(itemStatus), m_favourite(favourite) {
    try {
        boost::uuids::string_generator gen;
        m_uuid = gen(uuid);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Invalid UUID format: " + std::string(e.what()));
    }
}

std::string Item::getDescription() const {
    return m_description;
}

ItemStatus Item::getItemStatus() const {
    return m_itemStatus;
}

void Item::setDescription(const std::string& newDescription) {
    m_description = newDescription;
}

void Item::setItemStatus(const ItemStatus& newItemStatus) {
    m_itemStatus = newItemStatus;
}

std::string Item::getUuid() const {
    return boost::uuids::to_string(m_uuid);
}

bool Item::isFavourite() const
{
    return m_favourite;
}

void Item::setFavourite(bool new_favourite)
{
    m_favourite = new_favourite;
}

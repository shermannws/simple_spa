#pragma once

#include <string>
#include <memory>

#include "../HashableKey.h"
#include "EntityType.h"

class Entity: public HashableKey {
private:
    EntityType entityType;
    std::shared_ptr<std::string> entityValue;

public:
    /*!
     *  Constructor for Entity object
     */
    Entity(const std::shared_ptr<std::string> entityValue, EntityType entityType);

    /*!
     *  Destructor (virtual to allow polymorphic destruction)
     */
    virtual ~Entity() = default;

    /*!
     *  Return the Entity Type of the Entity of enum type `EntityType`
     */
    EntityType getEntityType() const;

    /*!
     *  Returns the string value of the entity
     */
    std::string* getEntityValue() const;

    /*!
     *  Equality operator to compare between Entities
     */
    bool operator==(const HashableKey& other) const override;
};

template <>
struct std::hash<Entity> {
    std::size_t operator()(const Entity& entity) const;
};

template <>
struct std::hash<std::shared_ptr<Entity>> {
    std::size_t operator()(const std::shared_ptr<Entity> entityPtr) const;
};

template<>
struct std::equal_to<std::shared_ptr<Entity>> {
    bool operator()(std::shared_ptr<Entity> const& lhs,
        std::shared_ptr<Entity> const& rhs) const;
};
#pragma once

#include <string>
#include <memory>

#include "../HashableKey.h"
#include "EntityType.h"
#include "../AppConstants.h"

/**
 * @brief An Entity is an entity in the SIMPLE programming language
 * @details An Entity is an entity in the SIMPLE programming language
 */
class Entity: public HashableKey {
private:
    /**
     * @brief The Entity Type of the Entity of enum type `EntityType`
     */
    EntityType entityType;
    /**
     * @brief The string value of the entity
     */
    std::shared_ptr<EntityValue> entityValue;
    /**
     * @brief True if the entity value is of type int, false otherwise
     */
    bool isInt;

public:
    /**
     * @brief Construct a new Entity object
     * @param entityValue The string value of the entity
     * @param isInt True if the entity is of type int, false otherwise
     * @param entityType The Entity Type of the Entity of enum type `EntityType`
     * @return A new Entity object
     */
    Entity(const std::shared_ptr<EntityValue> entityValue, EntityType entityType);

    /**
     * @brief Destroy the Entity object
     * @return None
     * @note Default destructor
     */
    virtual ~Entity() = default;

    /**
     * @brief Returns the Entity Type of the Entity object of enum type `EntityType`
     * @return The Entity Type of the Entity object of enum type `EntityType`
     */
    EntityType getEntityType() const;

    /**
     * @brief Returns the string value of the Entity object
     * @return The string value of the Entity object
     */
    EntityValue* getEntityValue() const;

    /**
     * @brief Returns true if the Entity value is of type int, false otherwise
     * @return True if the Entity value is of type int, false otherwise
     */
    bool isEntityOfTypeInt() const;

    /**
     * @brief Returns true if the Entity object is equal to the other Entity object, false otherwise
     * @param other The other Entity object to compare with
     * @return True if the Entity object is equal to the other Entity object, false otherwise
     */
    bool operator==(const HashableKey& other) const override;
};

/**
 * @brief A hash function for Entity objects
 * @details A hash function for Entity objects
 * @note This hash function is used by the EntityStore class
 */
template <>
struct std::hash<Entity> {
    std::size_t operator()(const Entity& entity) const;
};

/**
 * @brief A hash function for shared_ptr of Entity objects
 * @details A hash function for shared_ptr of Entity objects
 * @note This hash function is used by the EntityStore class
 */
template <>
struct std::hash<std::shared_ptr<Entity>> {
    std::size_t operator()(const std::shared_ptr<Entity> entityPtr) const;
};

/**
 * @brief An equal function for shared_ptr of Entity objects
 * @details An equal function for shared_ptr of Entity objects
 * @note This equal function is used by the EntityStore class
 */
template<>
struct std::equal_to<std::shared_ptr<Entity>> {
    bool operator()(std::shared_ptr<Entity> const& lhs,
        std::shared_ptr<Entity> const& rhs) const;
};
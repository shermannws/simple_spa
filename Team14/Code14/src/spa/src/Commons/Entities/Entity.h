#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../AppConstants.h"
#include "EntityType.h"

/**
 * @brief An Entity is an entity in the SIMPLE programming language
 * @details An Entity is an entity in the SIMPLE programming language
 */
class Entity {
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
     * @brief The secondary string value of the entity
     */
    std::shared_ptr<AttrValue> attrValue;

public:
    /**
     * Creates an empty Entity object.
     * CPP requires this to use Entity and its subclasses as a value in an (unordered) map.
     */
    Entity();

    /**
     * @brief Construct a new Entity object
     * @param entityValue The string value of the entity
     * @param entityType The Entity Type of the Entity of enum type `EntityType`
     * @return A new Entity object
     */
    Entity(const std::shared_ptr<EntityValue> entityValue, EntityType entityType);

    /**
     * @brief Construct a new Entity object
     * @param entityValue The string value of the entity
     * @param entityType The Entity Type of the Entity of enum type `EntityType`
     * @param attrValue The secondary string value of the entity
     * @return A new Entity object
     */
    Entity(const std::shared_ptr<EntityValue> entityValue, EntityType entityType,
           const std::shared_ptr<AttrValue> attrValue);

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
     * @brief Returns the EntityValue (of type string) of the Entity object
     * @return The EntityValue (of type string) of the Entity object
     */
    EntityValue getEntityValue() const;

    /**
     * @brief Returns the AttrValue (of type string) of the Entity object
     * @return The AttrValue (of type string) of the Entity object
     */
    AttrValue getAttrValue() const;

    /**
     * @brief Returns true if the Entity object is equal to the other Entity object, false otherwise
     * @param other The other Entity object to compare with
     * @return True if the Entity object is equal to the other Entity object, false otherwise
     */
    bool operator==(const Entity &other) const;
};

/**
 * @brief A hash function for shared_ptr of Entity objects
 * @details A hash function for shared_ptr of Entity objects
 * @note This hash function is used by the EntityStore class
 */
template<>
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
    bool operator()(std::shared_ptr<Entity> const &lhs, std::shared_ptr<Entity> const &rhs) const;
};

/**
 * @brief A hash function for vector of Entity shared pointers
 * @details A hash function for vector of Entity shares pointers
 */
template<>
struct std::hash<std::vector<std::shared_ptr<Entity>>> {
    std::size_t operator()(const std::vector<std::shared_ptr<Entity>> &entities) const;
};

/**
 * @brief An equal function for a vector of Entity shared pointers
 * @details An equal function for a vector of Entity shared pointers
 */
template<>
struct std::equal_to<std::vector<std::shared_ptr<Entity>>> {
    bool operator()(std::vector<std::shared_ptr<Entity>> const &lhs,
                    std::vector<std::shared_ptr<Entity>> const &rhs) const;
};
#pragma once

#include <string>
#include <memory>

#include "../HashableKey.h"

class Entity: public HashableKey {
private:
    std::shared_ptr<std::string> entityValue;
    bool isInt;

public:
    Entity(const std::shared_ptr<std::string> entityValue, bool isInt);
    virtual ~Entity() = default;

    std::string* getEntityValue() const;
    bool isEntityOfTypeInt() const;

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
#pragma once

#include <cstddef>
#include <functional>

/**
 * @brief A HashableKey is an interface that enforce the implementation of the hash function
 * @details A HashableKey is an interface that enforce the implementation of the hash function
 */
class HashableKey {
public:
    /**
     * @brief Destroy the HashableKey object
     */
    virtual ~HashableKey() = default;
};
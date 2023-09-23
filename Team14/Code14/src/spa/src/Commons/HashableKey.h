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

    /**
     * @brief Returns true if the HashableKey object is equal to the other HashableKey object, false otherwise
     * @param other The other HashableKey object to compare against
     * @return True if the HashableKey object is equal to the other HashableKey object, false otherwise
     */
    virtual bool operator==(const HashableKey& other) const = 0;
};

/**
 * @brief A hash function for HashableKey objects
 * @details A hash function for HashableKey objects
 */
template <>
struct std::hash<HashableKey> {
    /**
     * @brief Returns the hash value of the HashableKey object
     * @param key The HashableKey object to hash
     * @return The hash value of the HashableKey object
     */
    size_t operator()(const HashableKey& key) const;
};
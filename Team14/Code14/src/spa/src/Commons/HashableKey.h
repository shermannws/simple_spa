#pragma once

#include <cstddef>
#include <functional>

class HashableKey {
public:
    // Destructor (virtual to allow polymorphic destruction)
    virtual ~HashableKey() = default;

    // Define the equality operator (pure virtual)
    virtual bool operator==(const HashableKey& other) const = 0;
};

template <>
struct std::hash<HashableKey> {
    size_t operator()(const HashableKey& key) const;
};
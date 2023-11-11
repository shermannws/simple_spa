#pragma once

#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Type trait to test for presence of valid hash function during compilation.
 * This is the default template, and has a compile-time IsHashable::value value of false.
 * This version of the IsHashable struct will be used if the type T fails the std::hash check
 * for the specialized template, triggering SFINAE and falling back to this default version.
 * @tparam T Type to check for presence of valid hash function
 */
template<typename T, typename = void>
struct IsHashable : std::false_type {};

/**
 * Type trait to test for presence of valid hash function during compilation.
 * This is the specialized template, and has a compile-time IsHashable::value value of true.
 * This version of the IsHashable struct will be used when the std::hash check in the struct
 * declaration passes, i.e. no compilation error is thrown.
 * @tparam T Type to check for presence of valid hash function
 */
template<typename T>
struct IsHashable<T, decltype(std::hash<T>()(std::declval<T>()), void())> : std::true_type {};


/**
 * Union-Find Disjoint Set data structure.
 * @tparam T The type of elements that the UFDS will hold
 */
template<typename T>
class UFDSUtil {
private:
    inline static const int DEFAULT_RANK = 0;

    /**
     * The unordered map of each element to its parent.
     */
    std::unordered_map<T, T> parent;

    /**
     * The unordered map of each element to its rank to be used as part of the union-by-rank heuristic.
     */
    std::unordered_map<T, int> rank;

    /**
     * Adds a new set to the UFDS instance with an initial element.
     * Element should not already exist in the UFDS.
     * @param element The initial element of the set
     */
    void makeSet(const T &element);

public:
    /**
     * Creates an empty UFDS.
     */
    UFDSUtil();

    /**
     * Initializes a UFDS with a vector of elements.
     * @param elements The initial elements contained in the UFDS
     */
    explicit UFDSUtil(const std::vector<T> &elements);

    /**
     * Returns the representative (root) element of the set that this element is in.
     * Employs path compression. The element should already exist in the UFDS.
     * @param element The element whose set is to be found
     * @return The representative element of the set that the given element is in
     */
    T findSet(const T &element);

    /**
     * Returns whether two elements are in the same set.
     * Triggers path compression. The elements should already exist in the UFDS.
     * @param element1 The first element for comparison
     * @param element2 The second element for comparison
     * @return True if both elements are in the same set, else false
     */
    bool isSameSet(const T &element1, const T &element2);

    /**
     * Merges the sets that hold 2 elements.
     * Ignores if both elements are already in the same set.
     * Adds any element to the UFDS if it doesnt already exist.
     * Creates any non-existing elements in the UFDS.
     * Triggers path compression.
     * @param element1
     * @param element2
     */
    void unionSet(const T &element1, const T &element2);

    /**
     * Returns a reference to the underlying unordered map of each element to its parent.
     * @return The unordered map of each element to its parent
     */
    const std::unordered_map<T, T> &getParent() const;
};

#include "UFDSUtil.hpp"
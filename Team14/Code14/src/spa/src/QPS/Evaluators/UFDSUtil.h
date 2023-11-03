#pragma once

#include <unordered_map>
#include <vector>

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
     * Adds a new set to the UFDS instance with an initial element.
     * Ignores if the element already exists.
     * @param element The initial element of the set
     */
    void makeSet(const T &element);

    /**
     * Returns the representative (root) element of the set that this element is in.
     * Employs path compression. Adds the element to the UFDS if it doesnt already exist.
     * @param element The element whose set is to be found
     * @return The representative element of the set that the given element is in
     */
    T findSet(const T &element);

    /**
     * Returns whether two elements are in the same set.
     * Triggers path compression. Adds any element to the UFDS if it doesnt already exist.
     * @param element1 The first element for comparison
     * @param element2 The second element for comparison
     * @return True if both elements are in the same set, else false
     */
    bool isSameSet(const T &element1, const T &element2);

    /**
     * Merges the sets that hold 2 elements.
     * Ignores if both elements are already in the same set.
     * Adds any element to the UFDS if it doesnt already exist.
     * Triggers path compression.
     * @param element1
     * @param element2
     */
    void unionSet(const T &element1, const T &element2);
};

#include "UFDSUtil.hpp"
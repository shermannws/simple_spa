template<typename T>
UFDSUtil<T>::UFDSUtil() {
    static_assert(IsHashable<T>::value, "Type used in UFDS must have a hash function defined.");
};

template<typename T>
UFDSUtil<T>::UFDSUtil(const std::vector<T> &elements) {
    // Optional: add assert to test for presence of hash function for T
    static_assert(IsHashable<T>::value, "Type used in UFDS must have a hash function defined.");
    for (const T &element: elements) {
        parent.emplace(element, element);
        rank.emplace(element, DEFAULT_RANK);
    }
}

template<typename T>
void UFDSUtil<T>::makeSet(const T &element) {
    if (parent.find(element) == parent.end()) {
        parent[element] = element;
        rank[element] = DEFAULT_RANK;
    }
}

template<typename T>
T UFDSUtil<T>::findSet(const T &element) {
    if (parent.find(element) == parent.end()) { makeSet(element); }

    if (parent[element] == element) { return element; }

    // Path compression heuristic
    return parent[element] = findSet(parent[element]);
}

template<typename T>
bool UFDSUtil<T>::isSameSet(const T &element1, const T &element2) {
    return findSet(element1) == findSet(element2);
}

template<typename T>
void UFDSUtil<T>::unionSet(const T &element1, const T &element2) {
    if (isSameSet(element1, element2)) { return; }

    T root1 = findSet(element1);
    T root2 = findSet(element2);

    if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    } else if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    } else {
        // default case when both have the same rank
        // can use randomization if performance needs improvement
        parent[root2] = root1;
        rank[root1]++;
    }
}
template <typename K, typename V, typename H>
MapStore<K, V, H>::MapStore() = default;

template <typename K, typename V, typename H>
void MapStore<K, V, H>::store(std::shared_ptr<K> key, std::shared_ptr<V> value) {
    this->mapStore.insert({left, right});
}

template <typename K, typename V, typename H>
typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<V>>::iterator MapStore<K, V, H>::getBeginIterator() {
    return this->mapStore.begin();
}

template <typename K, typename V, typename H>
typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<V>>::iterator MapStore<K, V, H>::getEndIterator() {
    return this->mapStore.end();
}

template <typename K, typename V, typename H>
std::shared_ptr<V> getValueOf(std::shared_ptr<K> key) const {
    if (this->mapStore.find(key) == this->mapStore.end()) {
        return nullptr;
    }
    return this->mapStore.at(key);
}
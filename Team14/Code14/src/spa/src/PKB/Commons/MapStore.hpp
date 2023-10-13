template <typename K, typename V>
MapStore<K, V>::MapStore() = default;

template <typename K, typename V>
void MapStore<K, V>::setMapStore(std::unordered_map<K, std::shared_ptr<V>> map) {
	this->mapStore = map;
}

template <typename K, typename V>
typename std::unordered_map<K, std::shared_ptr<V>>::iterator MapStore<K, V>::getBeginIterator() {
    return this->mapStore.begin();
}

template <typename K, typename V>
typename std::unordered_map<K, std::shared_ptr<V>>::iterator MapStore<K, V>::getEndIterator() {
    return this->mapStore.end();
}

template <typename K, typename V>
std::shared_ptr<V> MapStore<K, V>::getValueOf(K key) const {
    if (this->mapStore.find(key) == this->mapStore.end()) {
        return nullptr;
    }
    return this->mapStore.at(key);
};
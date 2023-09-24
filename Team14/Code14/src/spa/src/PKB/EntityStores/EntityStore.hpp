template <typename T>
EntityStore<T>::EntityStore() = default;

template <typename T>
void EntityStore<T>::storeEntity(std::shared_ptr<T> entity) {
    this->entityStore.insert(entity);
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator EntityStore<T>::getBeginIterator() {
    return this->entityStore.begin();
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator EntityStore<T>::getEndIterator() {
    return this->entityStore.end();
}

template <typename T>
std::shared_ptr<Entity> EntityStore<T>::getEntity(std::shared_ptr<T> entity) const {
    typename std::unordered_set<std::shared_ptr<T>>::const_iterator got = this->entityStore.find(entity);
    if (got == this->entityStore.end()) {
        return nullptr;
    }
    return *got;
}
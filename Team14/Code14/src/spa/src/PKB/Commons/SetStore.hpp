template<typename T, typename H>
SetStore<T, H>::SetStore() = default;

template<typename T, typename H>
void SetStore<T, H>::store(std::shared_ptr<T> object) {
    this->storage.insert(object);
}

template<typename T, typename H>
typename std::unordered_set<std::shared_ptr<T>>::iterator
SetStore<T, H>::getBeginIterator() {
    return this->storage.begin();
}

template<typename T, typename H>
typename std::unordered_set<std::shared_ptr<T>>::iterator
SetStore<T, H>::getEndIterator() {
    return this->storage.end();
}

template<typename T, typename H>
bool SetStore<T, H>::isEmpty() const {
    return this->storage.empty();
}

template<typename T, typename H>
std::shared_ptr<T> SetStore<T, H>::get(std::shared_ptr<T> object) const {
    auto it = this->storage.find(object);
    if (it == this->storage.end()) { return nullptr; }
    return *it;
}
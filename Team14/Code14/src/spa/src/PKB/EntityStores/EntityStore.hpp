template <typename T>
EntityStore<T>::EntityStore() : SetStore<T, Entity>() {}

template <typename T>
void EntityStore<T>::storeEntity(std::shared_ptr<T> entity) {
    this->store(entity);
}

template <typename T>
std::shared_ptr<Entity> EntityStore<T>::getEntity(std::shared_ptr<T> entity) const {
    return this->get(entity);
}
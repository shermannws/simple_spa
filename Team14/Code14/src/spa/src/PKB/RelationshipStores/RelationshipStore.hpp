template <typename T, typename U>
RelationshipStore<T, U>::RelationshipStore() = default;

template <typename T, typename U>
void RelationshipStore<T, U>::storeRelationship(std::shared_ptr<T> left, std::shared_ptr<U> right) {
    if (this->leftToRightStore.find(left) == this->leftToRightStore.end()) {
        this->leftToRightStore.insert({ left, std::make_shared<EntityStore<U>>() });
    }
    this->leftToRightStore[left]->storeEntity(right);

    if (this->rightToLeftStore.find(right) == this->rightToLeftStore.end()) {
        this->rightToLeftStore.insert({right, std::make_shared<EntityStore<T>>()});
    }
    this->rightToLeftStore[right]->storeEntity(left);
}

template <typename T, typename U>
std::shared_ptr<EntityStore<U>> RelationshipStore<T, U>::getRightEntitiesOf(std::shared_ptr<T> left) const {
    if (this->leftToRightStore.find(left) == this->leftToRightStore.end()) {
        return nullptr;
    }
    return this->leftToRightStore.at(left);
}

template <typename T, typename U>
std::shared_ptr<EntityStore<T>> RelationshipStore<T, U>::getLeftEntitiesOf(std::shared_ptr<U> right) const {
    if (this->rightToLeftStore.find(right) == this->rightToLeftStore.end()) {
        return nullptr;
    }
    return this->rightToLeftStore.at(right);
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator RelationshipStore<T, U>::getLeftToRightBeginIterator() {
    return this->leftToRightStore.begin();
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator RelationshipStore<T, U>::getLeftToRightEndIterator() {
    return this->leftToRightStore.end();
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator RelationshipStore<T, U>::getRightToLeftBeginIterator() {
    return this->rightToLeftStore.begin();
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator RelationshipStore<T, U>::getRightToLeftEndIterator() {
    return this->rightToLeftStore.end();
}

template <typename T, typename U>
bool RelationshipStore<T, U>::isEmpty() const {
    return this->leftToRightStore.empty() && this->rightToLeftStore.empty();
}
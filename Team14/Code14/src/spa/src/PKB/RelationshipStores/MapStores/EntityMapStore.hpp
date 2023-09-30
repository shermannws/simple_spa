template <typename T, typename U>
EntityMapStore<T, U>::EntityMapStore() {}

template <typename T, typename U>
void EntityMapStore<T, U>::storeRelationship(std::shared_ptr<T> left, std::shared_ptr<U> right) {
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
std::shared_ptr<EntityStore<U>> EntityMapStore<T, U>::getRightEntitiesOf(std::shared_ptr<T> left) const {
    if (this->leftToRightStore.find(left) == this->leftToRightStore.end()) {
		return nullptr;
	}
    return this->leftToRightStore.at(left);
}

template <typename T, typename U>
std::shared_ptr<EntityStore<T>> EntityMapStore<T, U>::getLeftEntitiesOf(std::shared_ptr<U> right) const {
    if (this->rightToLeftStore.find(right) == this->rightToLeftStore.end()) {
		return nullptr;
	}
	return this->rightToLeftStore.at(right);
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator EntityMapStore<T, U>::getLeftToRightBeginIterator() {
    return this->leftToRightStore.begin();
}

template <typename T, typename U>
typename std::unordered_map<std::shared_ptr<T>, std::shared_ptr<EntityStore<U>>>::iterator EntityMapStore<T, U>::getLeftToRightEndIterator() {
	return this->leftToRightStore.end();
}
template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
DoubleMapStore<K1, K2, V1, V2, H1, H2>::DoubleMapStore() = default;

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
void DoubleMapStore<K1, K2, V1, V2, H1, H2>::store(std::shared_ptr<K1> left, std::shared_ptr<K2> right) {
    if (this->leftToRightStore.find(left) == this->leftToRightStore.end()) {
        this->leftToRightStore.insert({left, std::make_shared<V1>()});
    }
    this->leftToRightStore[left]->store(right);

    if (this->rightToLeftStore.find(right) == this->rightToLeftStore.end()) {
        this->rightToLeftStore.insert({right, std::make_shared<V2>()});
    }
    this->rightToLeftStore[right]->store(left);

    this->pairs.insert({left, right});
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
std::shared_ptr<V1> DoubleMapStore<K1, K2, V1, V2, H1, H2>::getRightEntitiesOf(std::shared_ptr<K1> left) const {
    if (this->leftToRightStore.find(left) == this->leftToRightStore.end()) { return nullptr; }
    return this->leftToRightStore.at(left);
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
std::shared_ptr<V2> DoubleMapStore<K1, K2, V1, V2, H1, H2>::getLeftEntitiesOf(std::shared_ptr<K2> right) const {
    if (this->rightToLeftStore.find(right) == this->rightToLeftStore.end()) { return nullptr; }
    return this->rightToLeftStore.at(right);
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
typename std::unordered_map<std::shared_ptr<K1>, typename std::shared_ptr<V1>>::iterator
DoubleMapStore<K1, K2, V1, V2, H1, H2>::getLeftToRightBeginIterator() {
    return this->leftToRightStore.begin();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
typename std::unordered_map<std::shared_ptr<K1>, typename std::shared_ptr<V1>>::iterator
DoubleMapStore<K1, K2, V1, V2, H1, H2>::getLeftToRightEndIterator() {
    return this->leftToRightStore.end();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
typename std::unordered_map<std::shared_ptr<K2>, typename std::shared_ptr<V2>>::iterator
DoubleMapStore<K1, K2, V1, V2, H1, H2>::getRightToLeftBeginIterator() {
    return this->rightToLeftStore.begin();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
typename std::unordered_map<std::shared_ptr<K2>, typename std::shared_ptr<V2>>::iterator
DoubleMapStore<K1, K2, V1, V2, H1, H2>::getRightToLeftEndIterator() {
    return this->rightToLeftStore.end();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
bool DoubleMapStore<K1, K2, V1, V2, H1, H2>::isEmpty() const {
    return this->leftToRightStore.empty() && this->rightToLeftStore.empty();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
void DoubleMapStore<K1, K2, V1, V2, H1, H2>::clear() {
    this->leftToRightStore.clear();
    this->rightToLeftStore.clear();
}

template<typename K1, typename K2, typename V1, typename V2, typename H1, typename H2>
EntityPairSet DoubleMapStore<K1, K2, V1, V2, H1, H2>::getPairs() const {
    return this->pairs;
}
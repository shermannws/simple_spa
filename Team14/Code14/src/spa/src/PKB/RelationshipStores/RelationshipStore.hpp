#pragma once

template <typename T>
RelationshipStore<T>::RelationshipStore() {}

template <typename T>
void RelationshipStore<T>::storeRelationship(std::shared_ptr<T> relationship) {
    this->relationshipStore.insert(relationship);
}

template <typename T>
std::shared_ptr<T> RelationshipStore<T>::getRelationship(std::shared_ptr<T> relationship) const {
    typename std::unordered_set<std::shared_ptr<T>>::const_iterator got = this->relationshipStore.find(relationship);
    if (got == this->relationshipStore.end()) {
        return nullptr;
    }
    return *got;
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator RelationshipStore<T>::getBeginIterator() {
    return this->relationshipStore.begin();
}

template <typename T>
typename std::unordered_set<std::shared_ptr<T>>::iterator RelationshipStore<T>::getEndIterator() {
    return this->relationshipStore.end();
}

template <typename T>
bool RelationshipStore<T>::isEmpty() const {
    return this->relationshipStore.empty();
}
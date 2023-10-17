template<typename T, typename U>
RelationshipStore<T, U>::RelationshipStore()
    : DoubleMapStore<T, U, EntityStore<U>, EntityStore<T>, Entity, Entity>() {}

template<typename T, typename U>
void RelationshipStore<T, U>::storeRelationship(std::shared_ptr<T> left,
                                                std::shared_ptr<U> right) {
    this->store(left, right);
}
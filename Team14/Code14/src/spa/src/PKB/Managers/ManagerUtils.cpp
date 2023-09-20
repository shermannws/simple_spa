#include "ManagerUtils.h"

template <typename S, typename R>
std::vector<Entity> ManagerUtils::getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter) {
    auto result = std::vector<Entity>();
    for (auto it = store->getBeginIterator(); it != store->getEndIterator(); it++) {
        if (matcher(**it)) {
            result.push_back(getter(**it));
        }
    }
    return result;
}
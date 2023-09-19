#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Commons/Entities/Entity.h"

class ManagerUtils {
public:
    template<typename S, typename R>
    static std::vector<Entity>
    getFromStore(std::shared_ptr<S> store, std::function<bool(R&)> matcher, std::function<Entity(R&)> getter);
};

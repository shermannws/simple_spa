#pragma once

#include "Commons/EntityFactory.h"

/**
 * A class used to inject setup and cleanup operations to unit test cases.
 */
class UnitTestFixture : EntityFactory {
public:
    /**
     * Runs before each test case. Setup operations here.
     */
    UnitTestFixture();

    /**
     * Runs after each test case. Cleanup operations here.
     */
    ~UnitTestFixture();
};

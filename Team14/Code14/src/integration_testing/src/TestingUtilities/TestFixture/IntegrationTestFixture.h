#pragma once

#include "Commons/EntityFactory.h"

/**
 * A class used to inject setup and cleanup operations to integration test cases.
 */
class IntegrationTestFixture : EntityFactory {
public:
    /**
     * Runs before each test case. Setup operations here.
     */
    IntegrationTestFixture();

    /**
     * Runs after each test case. Cleanup operations here.
     */
    ~IntegrationTestFixture();
};

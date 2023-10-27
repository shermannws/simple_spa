#include "IntegrationTestFixture.h"

IntegrationTestFixture::IntegrationTestFixture() { EntityFactory::clearCaches(); }

IntegrationTestFixture::~IntegrationTestFixture() { EntityFactory::clearCaches(); }
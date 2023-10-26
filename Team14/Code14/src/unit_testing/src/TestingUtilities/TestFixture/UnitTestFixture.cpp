#include "UnitTestFixture.h"

UnitTestFixture::UnitTestFixture() { EntityFactory::clearCaches(); }

UnitTestFixture::~UnitTestFixture() { EntityFactory::clearCaches(); }
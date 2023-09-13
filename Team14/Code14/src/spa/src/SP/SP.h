#pragma once

#include <memory>

#include "PKB/PkbWriter.h"

class SP {
private:
	std::shared_ptr<PkbWriter> pkbWriter;

public:
	SP(std::shared_ptr<PkbWriter> pkbWriter);
	void startSPProcessing(std::string& input);
};
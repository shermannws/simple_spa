#pragma once

class Statement {
private:
	int lineNo;

public:
	Statement(int lineNo);
	int getLineNo();
};
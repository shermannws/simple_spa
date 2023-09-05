#pragma once

#include <string>
using namespace std;

class Variable {
private:
	string name;

public:
	Variable(string name);
	string getName();
};
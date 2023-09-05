#pragma once

#include <string>
using namespace std;

class Procedure {
private:
	string name;

public:
	Procedure(string name);
	string getName();
};
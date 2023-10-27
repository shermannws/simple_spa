#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <iostream>
#include <list>
#include <string>

// include your other headers here
#include "AbstractWrapper.h"
#include "PKB/PkbConcreteReader.h"
#include "PKB/PkbConcreteWriter.h"

class TestWrapper : public AbstractWrapper {
private:
    std::shared_ptr<PkbWriter> pkbWriter;
    std::shared_ptr<PkbReader> pkbReader;

public:
    // default constructor
    TestWrapper();

    // destructor
    ~TestWrapper();

    // method for parsing the SIMPLE source
    virtual void parse(std::string filename);

    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string> &results);
};

#endif

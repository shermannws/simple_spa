#include "catch.hpp"
#include "SP/CFG/CFGBuilder.h"
#include "SP/SPTokenizer.h"
#include "SP/SPParser.h"

TEST_CASE("Test single procedure") {
    std::string sourceProgram =
            "procedure Proc1 {"
                "x = 1 + 2 * y - (1 / var) % 5;"
                "read x;"
                "print y;"
                "if (x > 1) then {"
                    "z = y;"
                "} else {"
                    "var1 = 5;"
                "} "
                "while (1 != 3) {"
                    "print c;"
                "}"
            "}";
    SPTokenizer tokenizer = SPTokenizer(sourceProgram);
    auto tokens = tokenizer.tokenize();
    SPParser parser;
    auto rootNode = parser.parse(tokens);

    CFGBuilder builder;
    REQUIRE_NOTHROW(builder.buildAllCFG(rootNode));
}

TEST_CASE("Test multiple procedures") {

}

TEST_CASE("Test nested ifs") {

}

TEST_CASE("Test nested whiles") {

}

TEST_CASE("Test complicated nested ifs and whiles") {

}

#include "SP/SPTokenizer.h"

#include <iostream>
#include <fstream>
#include <string>
#include "catch.hpp"

TEST_CASE("SPTokenizer tokenize name test") {
    std::string input = "var1 var2 var3 var4";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 4);

    // check each token individually using .at() method
    REQUIRE(tokens.at(0).getType() == TokenType::NAME);
    REQUIRE(tokens.at(0).getValue() == "var1");
    REQUIRE(tokens.at(1).getValue() == "var2");
    REQUIRE(tokens.at(2).getValue() == "var3");
    REQUIRE(tokens.at(3).getValue() == "var4");
}

TEST_CASE("SPTokenizer tokenize name with whitespace test") {
    std::string input = "var1   var2";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 2);

    // check each token individually using .at() method
    REQUIRE(tokens.at(0).getType() == TokenType::NAME);
    REQUIRE(tokens.at(0).getValue() == "var1");
    REQUIRE(tokens.at(1).getValue() == "var2");
}

TEST_CASE("SPTokenizer tokenize name and int test") {
    std::string input = "var1 123 var2 456";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 4);

    // check each token individually using .at() method
    REQUIRE(tokens.at(0).getType() == TokenType::NAME);
    REQUIRE(tokens.at(0).getValue() == "var1");
    REQUIRE(tokens.at(1).getType() == TokenType::INTEGER);
    REQUIRE(tokens.at(1).getValue() == "123");
    REQUIRE(tokens.at(2).getType() == TokenType::NAME);
    REQUIRE(tokens.at(2).getValue() == "var2");
    REQUIRE(tokens.at(3).getType() == TokenType::INTEGER);
    REQUIRE(tokens.at(3).getValue() == "456");
}

TEST_CASE("SPTokenizer tokenize name and int with white space test") {
    std::string input = "1 2 3 456 001 100 100000 1x10";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 9);

}

TEST_CASE("SPTokenizer parenthesis test") {
    std::string input = "( hello world ) {1} {{}}";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 11);

}

TEST_CASE("SPTokenizer semicolon and equals test") {
    std::string input = "(=);{abc 123xyz}";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();


}

TEST_CASE("SPTokenizer arithmetic test") {
    std::string input = "1+2-3*4/5%6";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();
}

//TEST_CASE("File Reading Test", "[file]") {
//    std::string fileContent;
//    std::string filePath = "../../../tests/positive_source/Test_source1.txt";
//    std::ifstream inputFile(filePath);
//
//    if (inputFile.is_open()) {
//        std::string line;
//        while (std::getline(inputFile, line)) {
//            fileContent += line + '\n';
//        }
//        inputFile.close();
//    } else {
//        FAIL("Failed to open file");
//    }
//
//    SPTokenizer tokenizer(fileContent);
//    std::vector<SPToken> tokens = tokenizer.tokenize();

    // Perform assertions to check the file content
//    REQUIRE(fileContent == "procedure computeAverage {\n"
//                           "    read num1;\n"
//                           "    read num2;\n"
//                           "    read num3;\n"
//                           "\n"
//                           "    sum = num1 + num2 + num3;\n"
//                           "    ave = sum / 3;\n"
//                           "\n"
//                           "    print ave;\n"
//                           "}");
//}

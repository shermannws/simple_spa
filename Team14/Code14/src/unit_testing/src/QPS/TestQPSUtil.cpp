#include "QPS/QPSUtil.h"

#include "catch.hpp"

std::string validVarName = "abc123";
std::string invalidVarName = "123abc";
std::string validConstValue = "123";
std::string invalidConstValue = "01";

TEST_CASE("IsVarName") {
    std::string s = "abc123";
    REQUIRE(QPSUtil::IsVarName(s));

    s = "123abc";
    REQUIRE(!QPSUtil::IsVarName(s));
}

TEST_CASE("IsConstValue") {
    std::string s = "123";
    REQUIRE(QPSUtil::IsConstValue(s));

    s = "123abc";
    REQUIRE(!QPSUtil::IsConstValue(s));

    s = "01";
    REQUIRE(!QPSUtil::IsConstValue(s));
}

TEST_CASE("IsFactor") {
    REQUIRE(QPSUtil::IsFactor(validVarName));
    REQUIRE(QPSUtil::IsFactor(validConstValue));
    REQUIRE(QPSUtil::IsFactor("(" + validVarName + ")"));
    REQUIRE(QPSUtil::IsFactor("(x+1)"));
    REQUIRE(QPSUtil::IsFactor("(x/y)"));
    REQUIRE(!QPSUtil::IsFactor("x+y"));
    REQUIRE(!QPSUtil::IsFactor("(xy+)"));
    REQUIRE(!QPSUtil::IsFactor("(x+y"));
    REQUIRE(!QPSUtil::IsFactor("()"));
}

TEST_CASE("IsTerm") {
    REQUIRE(QPSUtil::IsTerm(validVarName));
    REQUIRE(QPSUtil::IsTerm(validConstValue));
    REQUIRE(QPSUtil::IsTerm("(" + validVarName + ")"));
    REQUIRE(QPSUtil::IsTerm("x*12"));
    REQUIRE(QPSUtil::IsTerm("x%y"));
    REQUIRE(QPSUtil::IsTerm("1/2"));
    REQUIRE(QPSUtil::IsTerm("1*(x+y)"));
    //REQUIRE(QPSUtil::IsTerm("1*(x+y+z)"));
}

TEST_CASE("IsExpr") {
    REQUIRE(QPSUtil::IsExpr(validVarName));
    REQUIRE(QPSUtil::IsExpr("x+12"));
    REQUIRE(QPSUtil::IsExpr("x+12*y"));
    //REQUIRE(QPSUtil::IsExpr("(x+1)-1"));
}
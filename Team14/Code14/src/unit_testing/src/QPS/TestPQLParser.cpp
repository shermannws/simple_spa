#include "QPS/PQLParser.h"

#include "catch.hpp"

// TODO refactor unit tests using SECTION()

TEST_CASE("single declaration, single Select") {
    std::string input = "stmt s; Select s";
    PQLParser parser(input);
    Query query = parser.parse();
    QueryEntity expectedEntity = QueryEntity(QueryEntityType::Stmt, "s");
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("s");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(query.getEntity("s"));
    REQUIRE(*declarationEntity == expectedEntity);
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations serial declaration") {
    std::string input = "variable v,v1,v2; Select v";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("v");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==3);
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("v1"));
    REQUIRE(query.getEntity("v2"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations multiple declaration") {
    std::string input = "procedure p; stmt s; read re; print pr; assign a; \n call c; while w; if i; variable v; constant k; \n Select c";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("c");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==10);
    REQUIRE(query.getEntity("p"));
    REQUIRE(query.getEntity("s"));
    REQUIRE(query.getEntity("re"));
    REQUIRE(query.getEntity("pr"));
    REQUIRE(query.getEntity("a"));
    REQUIRE(query.getEntity("c"));
    REQUIRE(query.getEntity("w"));
    REQUIRE(query.getEntity("i"));
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("k"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("Select s ", "Expected a declaration but found none");
    testcases.emplace_back("assignment a; ", "Expected a declaration but found none");
    testcases.emplace_back("assign a Select s", "Expected ; but found 'Select'");
    testcases.emplace_back("assign a a1;", "Expected ; but found 'a1'");
    testcases.emplace_back("assign a; print a;", "Trying to redeclare a synonym");
    testcases.emplace_back("assign 1; Select 1", "Invalid synonym '1'");
    testcases.emplace_back("assign -a ; Select -a", "Invalid synonym '-'");
    testcases.emplace_back("stmt", "Expected synonym but found none");
    testcases.emplace_back("stmt ; ",  "Invalid synonym ';'");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

TEST_CASE("processSelect Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("stmt s; where s", "Expected Select clause but found 'where'");
    testcases.emplace_back("assign a; Select s", "Undeclared synonym in Select clause");
    testcases.emplace_back("assign a; Select", "Expected synonym but found none");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

TEST_CASE("processSuchThatClause Uses") {
    SECTION("Valid Uses query") {
        PQLParser parser("assign a; variable v;\nSelect a such that Uses(a, v)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "v");
    }

    SECTION("Valid Uses query") {
        PQLParser parser("assign a;\nSelect a such that Uses(\"main\",\"x\")"); // LHS is procedure
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "main");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "x");
    }

    SECTION("Valid Uses query") {
        PQLParser parser("assign x;\nSelect x such that Uses(x, \"x\")");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "x");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "x");
    }
}

TEST_CASE("processSuchThatClause Modifies") {
    SECTION("Valid Modifies(s,v) query") {
        PQLParser parser("stmt s; variable v; \nSelect v such that Modifies(s,v)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "v");
    }

    SECTION("Valid Modifies(s,ident) query") {
        PQLParser parser("read re; \nSelect re such that Modifies(re,\"variable\")");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "re");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "variable");
    }

    SECTION("Valid Modifies(integer,v) query") {
        PQLParser parser("variable l; \nSelect l such that Modifies(3,l)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "3");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "l");
    }

    SECTION("Valid Modifies(integer,ident) query") {
        PQLParser parser("stmt s; \nSelect s such that Modifies(1,\"hello\")");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "hello");
    }

    SECTION("Valid Modifies(s,_) query") {
        PQLParser parser("call a; \nSelect a such that Modifies(a,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Modifies(integer,_) query") {
        PQLParser parser("assign a; \nSelect a such that Modifies(5,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "5");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE("processSuchThatClause Follows") {
    SECTION("Valid Follows(s1,s2)") {
        PQLParser parser("stmt s1, s2;\nSelect s1 such that Follows (s1,s2)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Follows(s,integer)") {
        PQLParser parser("print pr;\nSelect pr  such  that  Follows(pr,1)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "pr");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Follows(s,_)") {
        PQLParser parser("if ifs;\nSelect ifs such that Follows(ifs,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Follows(integer,s)") {
        PQLParser parser("while w;\nSelect w such  that  Follows(1,w)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Follows(_,s)") {
        PQLParser parser("assign a;\nSelect a such that Follows(_,a)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Follows(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Follows(2,3)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Follows(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Follows(_,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE("processSuchThatClause Parent") {
    SECTION("Valid Parent(s1,s2)") {
        PQLParser parser("call s1, s2;\nSelect s1 such that Parent (s1,s2)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Parent(s,integer)") {
        PQLParser parser("print pr;\nSelect pr  such  that  Parent(pr,1)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "pr");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Parent(s,_)") {
        PQLParser parser("if ifs;\nSelect ifs such that Parent(ifs,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Parent(integer,s)") {
        PQLParser parser("while w;\nSelect w such  that  Parent(1,w)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Parent(_,s)") {
        PQLParser parser("assign a;\nSelect a such that Parent(_,a)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Parent(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent(2,3)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent(_,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE("processSuchThatClause Parent*") {
    SECTION("Valid Parent*(s1,s2)") {
        PQLParser parser("call s1, s2;\nSelect s1 such that Parent* (s1,s2)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Parent*(s,integer)") {
        PQLParser parser("assign assign;\nSelect assign such that  Parent*(assign,3)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "assign");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent*(s,_)") {
        PQLParser parser("read hello;\nSelect hello such that Parent*(hello,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "hello");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Parent*(integer,s)") {
        PQLParser parser("stmt read;\nSelect read such  that  Parent*(1,read)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "read");
    }

    SECTION("Valid Parent*(_,s)") {
        PQLParser parser("while while;\nSelect while such that Parent*(_,while)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "while");
    }

    SECTION("Valid Parent*(integer,integer)") {
        PQLParser parser("stmt s1; stmt s2;\nSelect s1  such  that  Parent*(2,3)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent*(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent*(_,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getFirstParam();
        Ref rightRef = clause.getSecondParam();
        REQUIRE(clause.getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE("Invalid processSuchThat cases") {
    SECTION("Invalid general queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a such",
                               "Invalid query syntax");
        testcases.emplace_back("assign a; print d;\nSelect a such that random(a",
                               "Invalid token, abstraction expected");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows* ",
                               "No left parenthesis");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a",
                               "No comma");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows(a, d",
                               "No right parenthesis");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Uses queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; variable v;\nSelect a such that Uses(_, v)",
                               "Invalid Uses LHS, wildcard found");
        testcases.emplace_back("assign a; variable v;\nSelect a such that Uses(v, a)",
                               "Invalid Uses LHS, invalid entity type found");
        testcases.emplace_back("call a; print d;\nSelect a such that Uses(\"y\", d)",
                               "Invalid Uses RHS, non-variable found");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(b, d)",
                               "Invalid Uses LHS, undeclared synonym found");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a, 2)",
                               "Invalid entRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Modifies queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; variable v;\nSelect a such that Modifies(_, v)",
                               "Invalid Modifies LHS, wildcard found");
        testcases.emplace_back("print a; constant v;\nSelect a such that Modifies(v, a)",
                               "Invalid Modifies LHS, invalid entity type found");
        testcases.emplace_back("call a; constant d;\nSelect a such that Modifies(\"test\", d)",
                               "Invalid Modifies RHS, non-variable found");
        testcases.emplace_back("stmt a; variable d;\nSelect a such that Modifies(b, d)",
                               "Invalid Modifies LHS, undeclared synonym found");
        testcases.emplace_back("print a; print d;\nSelect a such that Modifies(a, 3)",
                               "Invalid entRef");
        testcases.emplace_back("print a; variable d;\nSelect a such that Modifies(a, d)",
                               "Invalid Modifies LHS, invalid entity type found");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Follow queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; variable v;\nSelect v such that Follows(v, a)",
                               "Invalid Follows LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Follows(v, a)",
                               "Invalid Follows RHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Follows(hello, a)",
                               "Undeclared synonym found");
        testcases.emplace_back("procedure a; call v;\nSelect a such that Follows(\"hello\", v)",
                               "Invalid stmtRef");
        testcases.emplace_back("assign a; call v;\nSelect a such that Follows(a, \"world\")",
                               "Invalid stmtRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Parent queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; variable v;\nSelect v such that Parent(v, a)",
                               "Invalid Parent LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Parent(v, a)",
                               "Invalid Parent RHS, non-statement found");
        testcases.emplace_back("constant a; call v;\nSelect v such that Parent(a, v)",
                               "Invalid Parent LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Parent(hello, a)",
                               "Undeclared synonym found");
        testcases.emplace_back("stmt a; print v;\nSelect a such that Parent(\"hello\", v)",
                               "Invalid stmtRef");
        testcases.emplace_back("print a; assign v;\nSelect a such that Parent(a, \"world\")",
                               "Invalid stmtRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Parent* queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; variable v;\nSelect v such that Parent*(v, a)",
                               "Invalid Parent* LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Parent*(v, a)",
                               "Invalid Parent* RHS, non-statement found");
        testcases.emplace_back("constant a; call v;\nSelect v such that Parent*(a, v)",
                               "Invalid Parent* LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Parent*(hello, a)",
                               "Undeclared synonym found");
        testcases.emplace_back("stmt a; print v;\nSelect a such that Parent*(\"hello\", v)",
                               "Invalid stmtRef");
        testcases.emplace_back("print a; assign v;\nSelect a such that Parent*(a, \"world\")",
                               "Invalid stmtRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

}

//TEST_CASE("extractExpression") {
//    std::string input = "\"xy \"";
//    PQLParser parser(input);
//    auto final = parser.extractExpression();
//    REQUIRE(true);
//}
//
//TEST_CASE("extractExpressionSpec") {
//    std::string input = "_\"xy \"_";
//    PQLParser parser(input);
//    auto final = parser.extractExpressionSpec();
//    REQUIRE(true);
//}

TEST_CASE("processPatternClause") {
    SECTION("Valid wildcard pattern") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(_,_)");
        Query query = parser.parse();

        PatternClause actualClause = query.getPattern()[0];
        Ref leftRef = actualClause.getFirstParam();
        ExpressionSpec rightRef = actualClause.getSecondParam();
        REQUIRE(actualClause.getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second == "");
    }

    SECTION("Valid pattern, Synonym entRef and exact match") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(v,\"x+y\")");
        Query query = parser.parse();

        PatternClause actualClause = query.getPattern()[0];
        Ref leftRef = actualClause.getFirstParam();
        ExpressionSpec rightRef = actualClause.getSecondParam();
        REQUIRE(actualClause.getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getRep() == "v");
        REQUIRE(rightRef.first == ExpressionSpecType::ExactMatch);
        REQUIRE(rightRef.second == "((x)+(y))");
    }

    SECTION("Valid pattern, Synonym entRef and exact match") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(\"y\",_\"x*2\"_)");
        Query query = parser.parse();

        PatternClause actualClause = query.getPattern()[0];
        Ref leftRef = actualClause.getFirstParam();
        ExpressionSpec rightRef = actualClause.getSecondParam();
        REQUIRE(actualClause.getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "y");
        REQUIRE(rightRef.first == ExpressionSpecType::PartialMatch);
        REQUIRE(rightRef.second == "((x)*(2))");
    }


}

//TEST_CASE("processPatternClause") {
//    SECTION("Valid wildcard pattern") {
//        PQLParser parser("assign a; variable v;\nSelect a pattern a(_,_)");
//        Query query = parser.parse();
//
//        PatternClause actualClause = query.getPattern()[0];
//        Ref leftRef = actualClause.getFirstParam();
//        Ref rightRef = actualClause.getSecondParam();
//        REQUIRE(actualClause.getType() == ClauseType::Assign);
//        REQUIRE(leftRef.getType() == RefType::EntRef);
//        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
//        REQUIRE(leftRef.getRep() == "_");
//        REQUIRE(rightRef.getType() == RefType::EntRef);
//        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
//        REQUIRE(rightRef.getRep() == "_");
//    }
//
//    SECTION("Invalid pattern queries") {
//        std::vector<std::pair<std::string, std::string>> testcases;
//        testcases.emplace_back("assign a1; Select a1 pattern a(_,_)",
//                               "Undeclared synonym in pattern clause");
//        testcases.emplace_back("assign a1; variable v; Select a1 pattern a1 ( v,_)",
//                               "Expected wildcard as first arg");
//
//        for (const auto& testcase : testcases) {
//            PQLParser parser(testcase.first);
//            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
//        }
//    }
//
//}
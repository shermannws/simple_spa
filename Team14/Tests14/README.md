# System Testing for SPA by Team 14

## Folder Structure
The system test files are stored in subdirectories according to milestones (i.e. milestone1, milestone2 and milestone3)

## milestone1 test cases
The following are the subdirectories for `/milestone1`.
- QPS_multi_clause
  - Tests the combination of one such-that clause with one pattern clause.
- QPS_single_clause
  - Tests each such that clause individually.
  - Tests each pattern clause individually (assign pattern).
- SIMPLE_bad_syntax
  - Tests SIMPLE program with Syntax Error.
  - Note: The `_queries.txt` files in this subdirectory is empty as program would have terminated due to Syntax Error while parsing SIMPLE program.
- SIMPLE_minimal
  - Tests each statement type individually.
- SIMPLE_typical
  - Tests common and edge SIMPLE program to ensure that our program can handle the cases.

## milestone2 test cases
The following are the subdirectories for `/milestone2`.
- Extreme
  - Contains unncessarily long test cases to test the performance of the program.
- QPS_multi_clause
  - Tests the combination of multiple clauses together.
- QPS_select_clause
  - Tests the different types of select clauses newly introduced in milestone2.
- QPS_single_clause
  - Tests each such that clause individually.
  - Tests each pattern clause individually (assign/if/while pattern).
  - Tests each with clause individually.
- SIMPLE_bad_syntax
  - Tests SIMPLE program with Syntax or Semantic Error.
  - Note: The `_queries.txt` files in this subdirectory is empty as program would have terminated due to Error while parsing SIMPLE program.

## milestone3 test cases
The following are the subdirectories for `/milestone3`.
- Benchmark
  - Contains test cass for benchmarking and stress tests.
  - Tests mainly the optimization work done in milestone3.
- QPS_multi_clause
  - Tests the combination of multiple clauses together mainly involving "Affects" and "not".
- QPS_single_clause
  - Tests each such that clause individually (Affects).
  - Tests each "not" clause individually (permutation with each of the clauses tested exhaustively).
- Trivial
  - Tests queries which should return no values.
  - Example: Modifies(pn, v) should return none sinch pn is print synonym and print statements do not modify variables.
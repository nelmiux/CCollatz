// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(CollatzFixture, read_2) {
    string s("100 200\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 100, p.first);
    ASSERT_EQ( 200, p.second);}

TEST(CollatzFixture, read_3) {
    string s("201 210\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 201, p.first);
    ASSERT_EQ( 210, p.second);}

TEST(CollatzFixture, read_4) {
    string s("900 1000\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 900, p.first);
    ASSERT_EQ( 1000, p.second);}

TEST(CollatzFixture, read_5) {
    string s("1 1\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ( 1, p.second);}

TEST(CollatzFixture, read_6) {
    string s("7 27\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 7, p.first);
    ASSERT_EQ( 27, p.second);}

TEST(CollatzFixture, read_7) {
    string s("54 97\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 54, p.first);
    ASSERT_EQ( 97, p.second);}

TEST(CollatzFixture, read_8) {
    string s("10971 13255 255\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 0, p.first);
    ASSERT_EQ( 0, p.second);}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(7, 27);
    ASSERT_EQ(112, v);}
   
TEST(CollatzFixture, eval_7) {
    const int v = collatz_eval(54, 97);
    ASSERT_EQ(119, v);}
 
TEST(CollatzFixture, eval_8) {
    const int v = collatz_eval(10972, 13255);
    ASSERT_EQ(276, v);}

TEST(CollatzFixture, eval_9) {
    const int v = collatz_eval(1000000, 1000000);
    ASSERT_EQ(153, v);}

TEST(CollatzFixture, eval_10) {
    const int v = collatz_eval(-27, 7);
    ASSERT_EQ(0, v);}

TEST(CollatzFixture, eval_11) {
    const int v = collatz_eval(0, 1);
    ASSERT_EQ(0, v);}


// -----
// print
// -----

TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_EQ("100 200 125\n", w.str());}

TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());}

TEST(CollatzFixture, print_4) {
    ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_EQ("900 1000 174\n", w.str());}

TEST(CollatzFixture, print_5) {
    ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str());}
    
TEST(CollatzFixture, print_6) {
    ostringstream w;
    collatz_print(w, 912260, 188071, 525);
    ASSERT_EQ("912260 188071 525\n", w.str());}

TEST(CollatzFixture, print_7) {
    ostringstream w;
    collatz_print(w, 210, 201, 89);
    ASSERT_EQ("210 201 89\n", w.str());}
   
TEST(CollatzFixture, print_8) {
    ostringstream w;
    collatz_print(w, -27, 7, 2);
    ASSERT_EQ("", w.str());}


// -----
// solve
// -----

TEST(CollatzFixture, solve_1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(CollatzFixture, solve_2) {
    istringstream r("1 1\n912260 188071\n210 201\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n912260 188071 525\n210 201 89\n", w.str());}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/

// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <climits>

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    /*read s, a string
    return a pair of two ints, representing the beginning and end of a range, [i, j]*/
    istringstream sin(s);
    int i;
    int j;
    try {
        sin >> i >> j;
        int k;
        if ((sin >> k) != NULL) return make_pair(0, 0);
    } 
    catch (...) {
        return make_pair(0, 0);
    }
    return make_pair(i, j);}

// ------------
// collatz_length
// ------------

int collatz_length (int k) {
    /* calculate the cycle length of n
    return the cycle length of an integer n */
    uint64_t l = 1;
    uint64_t un_k = uint64_t(k);
    while (un_k != 1) {
        if (!(un_k % 2)) un_k = un_k >> 1;
        else {
            un_k = (3 * un_k + 1) >> 1;
            l += 1;
        }
        l += 1;
    }
    return l;
}


// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    /*return the max cycle length of the range [i, j]*/
    if  ((i < 1) || (j < 1) || (i > 1000000) || (j > 1000000))
        return 0;
    if (i == j) return collatz_length(i);
    uint64_t mx = 1;
    uint64_t cl = 0;
    for (uint64_t k = uint64_t(min(i,j)); k <= uint64_t(max(i,j)); k++) {
        cl = collatz_length(k);
        if ( cl > mx) mx = cl;
    }
    return int(mx);}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    if ((i < 1) || (j < 1) || (v < 1) || (w == NULL))
        w << "";
    else 
        w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

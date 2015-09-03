// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

// ------------
// collatz_read
// ------------

/*
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
pair<int, int> collatz_read (const string& s);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

// ------------
// collatz_read
// ------------

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}


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

int collatz_length (int n) {
    /* calculate the cycle length of n
    return the cycle length of an integer n */
    int l = 1;
    while (n != 1) {
        if (n % 2 == 0) n = n / 2;
        else {
            n = (3 * n + 1) / 2;
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
    int mx = 1;
    int cl = 0;
    for (int k = min(i,j); k <= max(i,j); k++) {
        cl = collatz_length(k);
        if ( cl > mx) mx = cl;
    }
    return mx;}

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

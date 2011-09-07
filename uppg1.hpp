#include <iostream>
#include <valarray>
#include <cstdlib>
#include <ctime>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>
#include "nn_common.hpp"

#define NDEBUG

//using namespace std;
using namespace boost::numeric::ublas;

//const int NEURONS = 200;
//const int PATTERNS = 30;
//const int TRIALS = 30;
#ifndef UPPG2
const bool reflexive = false;
#else
const bool reflexive = true;
#endif
RandomGenerator * gen;

void doTrials(int NEURONS, int PATTERNS, int TRIALS);
int doTrial(int NEURONS, int PATTERNS);

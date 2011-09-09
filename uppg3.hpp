#include <iostream>
#include <valarray>
#include <cstdlib>
#include <ctime>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_01.hpp>
#include "nn_common.hpp"

#define NDEBUG

//using namespace std;
using namespace boost::numeric::ublas;

//const int NEURONS = 200;
//const int PATTERNS = 30;
//const int TRIALS = 30;
const bool reflexive = false;

RandomGenerator * gen;

void doTrial(int neurons, int patterns, double betainv, int tmax);
double rand_sign(double b, double betainv);


#include <iostream>
#include <valarray>
#include <cstdlib>
#include <ctime>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp>

#define NDEBUG

//using namespace std;
using namespace boost::numeric::ublas;
	typedef boost::mt19937 RNGType;

//const int NEURONS = 200;
//const int PATTERNS = 30;
//const int TRIALS = 30;
#ifndef UPPG2
const bool reflexive = false;
#else
const bool reflexive = true;
#endif
boost::variate_generator<RNGType,boost::uniform_smallint<> > * gen;

void doTrials(int NEURONS, int PATTERNS, int TRIALS);
int doTrial(int NEURONS, int PATTERNS);
int sign(double x);
int random_plusminus_one();

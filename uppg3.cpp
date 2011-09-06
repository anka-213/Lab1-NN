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

int sign(double x) {
	if (x > 0) {
		return 1;
	} else if (x < 0) {
		return -1;
	
	} else { // if x = 0 (rare) interpret it as negative
		std::cout << "Zero" << std::endl;
		return 1;
	}
}

int random_plusminus_one() {
	return 2 *((*gen)()) - 1;
}


int main() {
	RNGType rng(std::time(0));         // produces randomness out of thin air
					    // see pseudo-random number generators
	boost::uniform_smallint<> zero_or_one(0,1);
					    // distribution that maps to 1..6
					    // see random number distributions
	gen = new boost::variate_generator<RNGType,boost::uniform_smallint<> > (rng,zero_or_one);
	
	boost::uniform_smallint<> number_of_neurons (50, 200);
	boost::uniform_smallint<> number_of_patterns (5, 100);
	std::cout << "N\tp\tP_fail" << std::endl;
	for (int i = 0; i < 1000; i++) {
		std::cerr << "[2K" << i;
		doTrials(number_of_neurons(rng),number_of_patterns(rng),30);
	}
}

void doTrials(int NEURONS, int PATTERNS, int TRIALS) {
	int sum = 0;
	for (int i = 0; i < TRIALS; i ++) {
		int fail = doTrial(NEURONS, PATTERNS);
		sum += fail;
	}
	double mean = (double) sum/TRIALS;
	std::cout << NEURONS << "\t" << PATTERNS << "\t" << mean << std::endl;
}

int doTrial(int NEURONS, int PATTERNS) {
	matrix<int> weight (NEURONS, NEURONS);
	vector<int> state (NEURONS);		 // Values -1 or 1
	matrix<int> pattern (NEURONS, PATTERNS); // Values -1 or 1
	//double weight[NEURONS][NEURONS];
	//int state[NEURONS];
	//int pattern[NEURONS][PATTERNS];


	// Store random patterns
	for (int mu = 0; mu < PATTERNS; mu++) {
		for (int i = 0; i < NEURONS; i++) {
			pattern(i, mu) = random_plusminus_one();
		//	std::cout << "Pattern[" << i << "][" << mu << "] = " << pattern[i][mu] << std::endl;
		}
	}
	
	for (int i = 0; i < NEURONS; i++) {
		for (int j = 0; j < NEURONS; j++) {
			if (i == j && ! reflexive) {
				weight(i, j) = 0;
			} else {
				int sum = 0;
				for (int mu = 0; mu < PATTERNS; mu++) {
					sum += pattern(i, mu) * pattern(j, mu);
				}
				weight(i, j) = sum;
			}
		//	std::cout << "Weight[" << i << "][" << j << "] = " << (float) weight[i][j]/PATTERNS << std::endl;
		}
	}

	// Our problem is symmetric, we can assume without loss
	// of generality that the first pattern is selected.
	int mu = 0;
	for (int i = 0; i < NEURONS; i++) {
		state(i) = pattern(i, mu); 
	}

	// Assume further that the first neuron is updated on the first iteration
	int i = 0;

	//for (int i = 0; i < 1; i++) {
	// state[i] = sign(sum over NEURONS j (weight[i][j]*state[j] / PATTERNS) - threshold[i])
	int sum = 0;
	for (int j = 0; j < NEURONS; j++) {
		sum += weight(i, j) * state(j);
	}
	int result = sign((float) sum/PATTERNS);
	//std::cout << "sum = " << sum << std::endl;

	int fail = (state(i) != result)?1:0;
	//}
	return fail;
}

// weight[i][i] = 0;
// weight[i][j] = 1.0/NEURONS * (sum over PATTERNS mu (pattern[i][mu] * pattern[j][mu]));

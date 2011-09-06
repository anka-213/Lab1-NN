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

//#define NDEBUG
#define sign(x) (( x > 0 ) - ( x < 0 ))

//using namespace std;
using namespace boost::numeric::ublas;

const int NEURONS = 20;
const int PATTERNS = 37;
const int TRIALS = 30000;
const bool reflexive = false;
boost::variate_generator<boost::rand48,boost::uniform_smallint<> > * gen;

double getWeight(int i, int j, matrix<int> &pattern);
int doTrial();

int random_plusminus_one() {
	return 2 *((*gen)()) - 1;
}


int main() {
	boost::rand48 rng(std::time(0));         // produces randomness out of thin air
					    // see pseudo-random number generators
	boost::uniform_smallint<> zero_or_one(0,1);
					    // distribution that maps to 1..6
					    // see random number distributions
	gen = new boost::variate_generator<boost::rand48,boost::uniform_smallint<> > (rng,zero_or_one);
	int sum = 0;
	for (int i = 0; i < TRIALS; i ++) {
		int fail = doTrial();
		sum += (fail == -1)? i--,0:fail; // I have found a wonderful
						  // proof that this works but
						  // there is not enough space
						  // in this marigin... 
	}
	double mean = (double) sum/TRIALS;
	std::cout << "P_fail = " << mean << " when N = " << NEURONS << ", p = "
	     << PATTERNS << " and n_trials = " << TRIALS << std::endl;
}

int doTrial() {
	matrix<double> weight (NEURONS, NEURONS);
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
	
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < NEURONS; j++) {
			weight(i, j) = getWeight(i,j, pattern);
		//	std::cout << "Weight[" << i << "][" << j << "] = " << weight[i][j] << std::endl;
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
	// state[i] = sign(sum over NEURONS j (weight[i][j]*state[j]) - threshold[i])
	double sum = 0;
	for (int j = 0; j < NEURONS; j++) {
		sum += weight(i, j) * state(j);
	}
	// std::cout << "sum = " << sum << std::endl;
	if (sign(sum) == 0) {
		std::cout << "sgn(0)" << std::endl;
		return -1;
	}
	// if (sign(sum) != state[i]) {
	// 	std::cout << "fail" << std::endl;
	// }
	// if (sign(sum) == state[i]) {
	// 	std::cout << "success" << std::endl;
	// }

	int fail = (state(i) != sign(sum))?1:0;
	//}
	return fail;
}

// weight[i][i] = 0;
// weight[i][j] = 1.0/NEURONS * (sum over PATTERNS mu (pattern[i][mu] * pattern[j][mu]));
double getWeight(int i, int j, matrix<int> &pattern) {
	if (i == j && ! reflexive) {
		return 0;
	} else {
		int sum = 0;
		for (int mu = 0; mu < PATTERNS; mu++) {
			sum += pattern(i, mu) * pattern(j, mu);
		}
		return (double) sum / PATTERNS;
	}
}

#include "uppg3.hpp"
#include <math.h>
//using namespace std;

RNGType * rng;

int main() {
	int neurons = 200;
	#ifdef five
	int patterns = 5;
	#endif
	#ifdef forty
	int patterns = 40;
	#endif
	double betainv = 0.5;

	// Initiate random generator
	rng = new RNGType(std::time(0));
	boost::uniform_smallint<> zero_or_one(0,1);
	gen = new boost::variate_generator<RNGType,boost::uniform_smallint<> > (*rng,zero_or_one);
	
	// Main loop
	for (int i = 0; i < 100; i++) {
		std::cout << std::endl;
		doTrial(neurons,patterns, betainv,6000);
	}
}

void doTrial(int neurons, int patterns, double betainv, int tmax) {
	matrix<int> weight (neurons, neurons);
	vector<int> state (neurons);		 // Values -1 or 1
	matrix<int> pattern (neurons, patterns); // Values -1 or 1
	//double weight[neurons][neurons];
	//int state[neurons];
	//int pattern[neurons][patterns];

	// Store random patterns
	generate_random_patterns(pattern, gen);
	
	//weight = prod(pattern, trans(pattern)) - neurons * identityMatrix(neurons);
	for (int i = 0; i < neurons; i++) {
		for (int j = 0; j < neurons; j++) {
			if (i == j) {
				weight(i, j) = 0;
			} else {
				int sum = 0;
				for (int mu = 0; mu < patterns; mu++) {
					sum += pattern(i, mu) * pattern(j, mu);
				}
				weight(i, j) = sum;
			}
		}
	}

	// Copy the first pattern to the state
	int mu = 0;
	for (int i = 0; i < neurons; i++) {
		state(i) = pattern(i, mu); 
	}

	for (int t=0; t<tmax ;t++) {
		// Pick random neuron i
		boost::uniform_smallint<> random_neuron(0,neurons-1);
		int neuron_nr = random_neuron(*rng);
	
		// Calculate and print m_1
		int sum1 = 0;
		for (int i = 0; i < neurons; i++) {
			sum1 += pattern(i, 0) * state(i);
		}
		double m_1 = (double) sum1 / neurons; 
		std::cout  << m_1  << "\t";

		// Calculate new value for neuron
		int sum = 0;
		for (int j = 0; j < neurons; j++) {
			sum += weight(neuron_nr, j) * state(j);
		}
		state(neuron_nr) = rand_sign((double) sum/neurons,betainv);
	}
}

// A sign function with random noise
// Sometimes it returns the opposite sign, depending on size of b and beta
double rand_sign(double b, double betainv) {
	boost::uniform_01<> dist;
	boost::variate_generator<RNGType,boost::uniform_01<> > generator(*rng,dist);
	double g = 1 / (1 + exp(-2 * b / betainv ));

	return (generator() < g)?1:-1;
}




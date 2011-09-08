#include "uppg3.hpp"
#include <math.h>
//using namespace std;

RNGType * rng;

int main() {
	rng = new RNGType(std::time(0));         // produces randomness out of thin air
					    // see pseudo-random number generators
	boost::uniform_smallint<> zero_or_one(0,1);
					    // distribution that maps to 1..6
					    // see random number distributions
	gen = new boost::variate_generator<RNGType,boost::uniform_smallint<> > (*rng,zero_or_one);
	
	int neurons = 200;
	#ifdef five
	int patterns = 5;
	#endif
	#ifdef forty
	int patterns = 40;
	#endif
	double betainv = 0.5;
	std::cout << "N\tp\tP_fail" << std::endl;
	for (int i = 0; i < 1; i++) {
		doTrial(neurons,patterns, betainv,1000);
	}
	// monitor m1(t)
}

int doTrial(int neurons, int patterns, double betainv, int tmax) {
	matrix<int> weight (neurons, neurons);
	vector<int> state (neurons);		 // Values -1 or 1
	matrix<int> pattern (neurons, patterns); // Values -1 or 1
	//double weight[neurons][neurons];
	//int state[neurons];
	//int pattern[neurons][patterns];

	// Store random patterns
	generate_random_patterns(pattern, gen);
	
	//weight = prod(pattern, trans(pattern));
// weight[i][i] = 0;
// weight[i][j] = 1.0/neurons * (sum over patterns mu (pattern[i][mu] * pattern[j][mu]));
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

	// Our problem is symmetric, we can assume without loss
	// of generality that the first pattern is selected.
	int mu = 0;
	for (int i = 0; i < neurons; i++) {
		state(i) = pattern(i, mu); 
	}
	//state(0) = -state(0);

	for (int t=0; t<tmax ;t++) {
		//Pick random i
		boost::uniform_smallint<> random_neuron(0,neurons-1);
		int neuron_nr = random_neuron(*rng);
	
		// Calculate and print m_1
		int sum1 = 0;
		for (int i = 0; i < neurons; i++) {
			sum1 += pattern(i, 0) * state(i);
		}
		double m_1 = (double) sum1 / neurons; 
		std::cout << neuron_nr << "\t" << m_1 << std::endl;
		
		
		// state[neuron_nr] = sign(sum over neurons j (weight[neuron_nr][j]*state[j] / patterns) - threshold[neuron_nr])
		int sum = 0;
		for (int j = 0; j < neurons; j++) {
			sum += weight(neuron_nr, j) * state(j);
		}
		state(neuron_nr) = rand_sign((double) sum/neurons,betainv);
		//std::cout << "sum = " << sum << std::endl;

		//state(neuron_nr) = g
	
	}

	//int fail = (state(i) != result)?1:0;
	//return fail;
	return 0;
}


double rand_sign(double b, double betainv) {
 
	
	double g = 1 / (1 + exp(-2 * b / betainv ));

	//double probabilities[] = { 1-g, g };
	boost::uniform_01<> dist;
	boost::variate_generator<RNGType,boost::uniform_01<> > generator(*rng,dist);
	
	double rnd = generator();
	//std::cout << "b = " << b << ", rnd = " << rnd << ", g = " << g << std::endl;
	return (rnd < g)?1:-1;
}




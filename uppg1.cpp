#include "uppg1.hpp"

int main() {
    RNGType rng(std::time(0));
    boost::uniform_smallint<> zero_or_one(0,1);
    gen = new boost::variate_generator<RNGType,
          boost::uniform_smallint<> > (rng,zero_or_one);
    
    boost::uniform_smallint<> number_of_neurons (50, 200);
    boost::uniform_smallint<> number_of_patterns (5, 100);
    std::cout << "N\tp\tP_fail" << std::endl;
    for (int i = 0; i < 1000; i++) {
    	std::cerr << "[2K" << i;
    	int non = number_of_neurons(rng);
    	int nop = number_of_patterns(rng);
    	doTrials(non,nop,30);
    }
}

void doTrials(int NEURONS, int PATTERNS, int TRIALS) {
    int sum = 0;
    for (int i = 0; i < TRIALS; i ++) {
    	int fail = doTrial(NEURONS, PATTERNS);
    	sum += fail;
    }
    double mean = (double) sum/TRIALS;
    std::cout << NEURONS << "\t" << PATTERNS <<
    	     "\t" << mean << std::endl;
}

int doTrial(int NEURONS, int PATTERNS) {
    matrix<int> weight (NEURONS, NEURONS);
    vector<int> state (NEURONS);	     // Values -1 or 1
    matrix<int> pattern (NEURONS, PATTERNS); // Values -1 or 1
    
    
    // Store random patterns
    generate_random_patterns(pattern, gen);
    
    // Calculate weights
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
    	}
    }
    
    // Our problem is symmetric, we can assume without loss
    // of generality that the first pattern is selected.
    int mu = 0;
    for (int i = 0; i < NEURONS; i++) {
    	state(i) = pattern(i, mu); 
    }
    
    // Assume further that the first neuron is updated
    // on the first iteration
    int i = 0;
    
    // Calculate new state for first neuron
    int sum = 0;
    for (int j = 0; j < NEURONS; j++) {
    	sum += weight(i, j) * state(j);
    }
    int result = sign((float) sum/PATTERNS);
    
    int fail = (state(i) != result)?1:0;
    return fail;
}





#include "nn_common.hpp"

int sign(double x) {
	// if x = 0 (rare) interpret it as negative
	if (x > 0) {
		return 1;
	} else if (x < 0) {
		return -1;
	}
}

int random_plusminus_one(RandomGenerator *gen) {
	return 2 *((*gen)()) - 1;
}


void generate_random_patterns(matrix<int> &pattern,
			      RandomGenerator *gen) {
	for (int mu = 0; mu < pattern.size2(); mu++) {
		for (int i = 0; i < pattern.size1() ; i++) {
		    pattern(i, mu) = random_plusminus_one(gen);
		}
	}
}

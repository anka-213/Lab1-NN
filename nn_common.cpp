#include "nn_common.hpp"

int sign(double x) {
	if (x > 0) { // if x = 0 (rare) interpret it as negative
		return 1;
	} else if (x < 0) {
		return -1;
	}
}

int random_plusminus_one(RandomGenerator *gen) {
	return 2 *((*gen)()) - 1;
}


void generate_random_patterns(matrix<int> &pattern, RandomGenerator *gen) {
	for (int mu = 0; mu < pattern.size2(); mu++) { // PATTERNS
		for (int i = 0; i < pattern.size1() ; i++) { // NEURONS
			pattern(i, mu) = random_plusminus_one(gen);
		//	std::cout << "Pattern[" << i << "][" << mu << "] = " << pattern[i][mu] << std::endl;
		}
	}
}
/*
void generate_weight_matrix(matrix<int> &pattern, bool reflexive) {
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
}
*/

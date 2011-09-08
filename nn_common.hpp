#include <boost/random.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

typedef boost::mt19937 RNGType;
typedef boost::variate_generator<RNGType,boost::uniform_smallint<> > RandomGenerator;

int sign(double x);
int random_plusminus_one(RandomGenerator *gen);
void generate_random_patterns(matrix<int> &pattern, RandomGenerator *gen);

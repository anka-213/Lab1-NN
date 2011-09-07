
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

using namespace boost::numeric::ublas;
	typedef boost::mt19937 RNGType;

boost::variate_generator<RNGType,boost::uniform_smallint<> > * gen;



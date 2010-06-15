#include "Random.h"
#include <cstdlib> // for time
#include "boost/bind.hpp"
#include <ctime>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
void Random::SetSeed()
{
  m_generator.seed(static_cast<unsigned int>(std::time(0)));
}

//----------------------------------------------------------------------------------------------------------------------
void Random::SetSeed(int _value)
{
  m_generator.seed(_value);
}


//----------------------------------------------------------------------------------------------------------------------
Random::Random()
{
  // we have two default generators built in

  // first create a simple uniform real distrib
  boost::uniform_real<ngl::Real> MinusPlusOneFloatDistrib(-1.0, 1.0);
  // create the generator
  boost::variate_generator<ENGINE &, boost::uniform_real<ngl::Real> >RandFloat(m_generator,MinusPlusOneFloatDistrib);
  // now assign the resultant function to the map for later use
  m_floatGenerators["RandomFloat"] =RandFloat;
  // same for below but using 0-1 for distrib
  boost::uniform_real<ngl::Real> ZeroOneFloatDistrib(0.0, 1.0);
  boost::variate_generator<ENGINE &, boost::uniform_real<ngl::Real> >RandPosFloat(m_generator,ZeroOneFloatDistrib);
  m_floatGenerators["RandomPositiveFloat"] =RandPosFloat;


}


//----------------------------------------------------------------------------------------------------------------------
ngl::Real Random::GetFloatFromGeneratorName(
                                            const std::string &_name
                                           )
{
  // grab a function pointer based on the _name from the map
  boost::function <ngl::Real (void)> func=m_floatGenerators[_name];
  // see if we got anything we can use
  if(func!=0)
  {
    // if it exists execute the function and return the value
    return func();
  }
  else
  {
    // otherwise we return the safest possible value 0
    return 0;
  }
}


//----------------------------------------------------------------------------------------------------------------------
ngl::Colour Random::GetRandomColour()
{
  // get our positive gen function and assign valus to a colour (alpha =1)
  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomPositiveFloat"];
	return ngl::Colour(gen(),gen(),gen());
}

//----------------------------------------------------------------------------------------------------------------------
ngl::Colour Random::GetRandomColourAndAlpha()
{
  // get our positive gen function and assign valus to a colour with rand alpha

  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomPositiveFloat"];
	return ngl::Colour(gen(),gen(),gen(),gen());
}

//----------------------------------------------------------------------------------------------------------------------
ngl::Vector Random::GetRandomVector()
{
  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomFloat"];
	return ngl::Vector(gen(),gen(),gen(),0.0f);
}

//----------------------------------------------------------------------------------------------------------------------
ngl::Vector Random::GetRandomNormalizedVector()
{
  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomFloat"];
	ngl::Vector v(gen(),gen(),gen(),0.0f);
  v.Normalize();
  return v;
}

//----------------------------------------------------------------------------------------------------------------------
ngl::Real Random::RandomNumber(ngl::Real _mult)
{
  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomFloat"];
	return gen()*_mult;
}

//----------------------------------------------------------------------------------------------------------------------
ngl::Real Random::RandomPositiveNumber(ngl::Real _mult)
{
  boost::function <ngl::Real (void)> gen=m_floatGenerators["RandomPositiveFloat"];
	return gen()*_mult;
}

//----------------------------------------------------------------------------------------------------------------------
void Random::AddGenerator(
                          const std::string &_name,
                          RANDDIST _distribution,
                          ngl::Real _min,
                          ngl::Real _max,
                          ngl::Real _prob
                         )
{
  /// this is rather tediously wrapping all the generators and attaching them to a
  /// generator and creating a map for it by name.
  if(_distribution== uniform_smallint)
  {
    boost::uniform_smallint<int> distrib(_min, _max);
    boost::variate_generator<ENGINE &, boost::uniform_smallint<int> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== uniform_int)
  {
    boost::uniform_int<int> distrib(_min, _max);
    boost::variate_generator<ENGINE &, boost::uniform_int<int> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }
  else if(_distribution== uniform_real)
  {
    boost::uniform_real<ngl::Real> distrib(_min, _max);
    boost::variate_generator<ENGINE &, boost::uniform_real<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }
  else if(_distribution== bernoulli_distribution)
  {
    boost::bernoulli_distribution<ngl::Real> distrib(_min);

    boost::variate_generator<ENGINE &, boost::bernoulli_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== binomial_distribution)
  {
    boost::binomial_distribution<ngl::Real> distrib(_min,_max);

    boost::variate_generator<ENGINE &, boost::binomial_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }
  else if(_distribution== cauchy_distribution)
  {
    boost::cauchy_distribution<ngl::Real> distrib(_min,_max);

    boost::variate_generator<ENGINE &, boost::cauchy_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }
  else if(_distribution== gamma_distribution)
  {
    boost::gamma_distribution<ngl::Real> distrib(_min);

    boost::variate_generator<ENGINE &, boost::gamma_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }
  else if(_distribution== poisson_distribution)
  {
    boost::poisson_distribution<int> distrib(_min);

    boost::variate_generator<ENGINE &, boost::poisson_distribution<int> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== geometric_distribution)
  {
    boost::geometric_distribution<int> distrib(_min);

    boost::variate_generator<ENGINE &, boost::geometric_distribution<int> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== triangle_distribution)
  {
    boost::triangle_distribution<ngl::Real> distrib(_min,_prob,_max);

    boost::variate_generator<ENGINE &, boost::triangle_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== exponential_distribution)
  {
    boost::exponential_distribution<ngl::Real> distrib(_min);

    boost::variate_generator<ENGINE &, boost::exponential_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== normal_distribution)
  {
    boost::normal_distribution<ngl::Real> distrib(_min,_max);

    boost::variate_generator<ENGINE &, boost::normal_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

  else if(_distribution== lognormal_distribution)
  {
    boost::lognormal_distribution<ngl::Real> distrib(_min,_max);

    boost::variate_generator<ENGINE &, boost::lognormal_distribution<ngl::Real> >gen(m_generator,distrib);
    m_floatGenerators[_name] =gen;
  }

}
//----------------------------------------------------------------------------------------------------------------------

}; // end of namespace




#include <iostream>
#include "ngl/Random.h"

int main()
{
  ngl::Random *rand=ngl::Random::Instance();
  rand->SetSeed();
  std::cout <<"Basic random number tests \n";
  std::cout<<rand->RandomNumber()<<std::endl;
  std::cout<<rand->RandomNumber(20)<<std::endl;
  std::cout<<rand->RandomPositiveNumber()<<std::endl;
  std::cout<<rand->RandomPositiveNumber(10)<<std::endl;

  std::cout <<"Using built in Generators \n";
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("RandomFloat")<<" ";
  }

  std::cout<<"\nrandom positive floats\n";
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("RandomPositiveFloat")<<" ";
  }

  std::cout<<"\nColours\n";
  std::cout<<rand->GetRandomColour()<<std::endl;
  std::cout<<rand->GetRandomColourAndAlpha()<<std::endl;
  std::cout<<"Vectors \n";
  std::cout<<rand->GetRandomVector()<<std::endl;
  std::cout<<rand->GetRandomNormalizedVector()<<std::endl;

  std::cout<<"Add Generators test\n";


  rand->AddGenerator("uniform_smallint",ngl::uniform_smallint,0,100);
  std::cout<<"uniform small int 0-100 ";
  for(int i=0; i<10; ++i)
  {
  std::cout<<rand->GetFloatFromGeneratorName("uniform_smallint")<<" ";
  }

  rand->AddGenerator("uniform_int",ngl::uniform_int,0,100);
  std::cout<<"\nuniform_int  0-100 ";
  for(int i=0; i<10; ++i)
  {
  std::cout<<rand->GetFloatFromGeneratorName("uniform_int")<<" ";
  }

  rand->AddGenerator("uniform_real",ngl::uniform_real,0,2.5);
  std::cout<<"\nuniform_real  0-2.5 ";
  for(int i=0; i<10; ++i)
  {
  std::cout<<rand->GetFloatFromGeneratorName("uniform_real")<<" ";
  }

  std::cout<<"\nbernoulli_distribution 0.5 ";
  rand->AddGenerator("bernoulli_distribution",ngl::bernoulli_distribution,0.5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("bernoulli_distribution")<<" ";
  }

  std::cout<<"\nbinomial_distribution t=0.2 p=0.5 \n";
  rand->AddGenerator("binomial_distribution",ngl::binomial_distribution,0.2,0.5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("binomial_distribution")<<" ";
  }
  std::cout<<"\ncauchy_distribution median 2 Sigma 5 \n";
  rand->AddGenerator("cauchy_distribution",ngl::cauchy_distribution,2,5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("cauchy_distribution")<<" ";
  }

  std::cout<<"\ngamma_distribution alpha= 5 \n";
  rand->AddGenerator("gamma_distribution",ngl::gamma_distribution,5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("gamma_distribution")<<" ";
  }

  std::cout<<"\npoisson_distribution mean= 2000 \n";
  rand->AddGenerator("poisson_distribution",ngl::poisson_distribution,2000);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("poisson_distribution")<<" ";
  }
  std::cout<<"\ngeometric_distribution p= 0.5 \n";
  rand->AddGenerator("geometric_distribution",ngl::geometric_distribution,0.5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("geometric_distribution")<<" ";
  }

  std::cout<<"\ntriangle_distribution min=10 max=30 prob=25 \n";
  rand->AddGenerator("triangle_distribution",ngl::triangle_distribution,10,30,25);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("triangle_distribution")<<" ";
  }

  std::cout<<"\nexponential_distribution lambda=25 \n";
  rand->AddGenerator("exponential_distribution",ngl::exponential_distribution,25);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("exponential_distribution")<<" ";
  }

  std::cout<<"\nnormal_distribution mean=25 sigma 0.5 \n";
  rand->AddGenerator("normal_distribution",ngl::normal_distribution,25,0.5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("normal_distribution")<<" ";
  }

  std::cout<<"\nlognormal_distribution mean=25 sigma 0.5 \n";
  rand->AddGenerator("lognormal_distribution",ngl::lognormal_distribution,25,0.5);
  for(int i=0; i<10; ++i)
  {
    std::cout<<rand->GetFloatFromGeneratorName("lognormal_distribution")<<" ";
  }

  std::cout<<"\nEnd of test\n";

}

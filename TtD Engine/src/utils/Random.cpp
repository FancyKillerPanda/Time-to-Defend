#include "pch.h"

#include "Random.h"


std::mt19937 Random::m_Rng;


void Random::init()
{
	// Seeds the generator
	m_Rng.seed(std::random_device()());
	LOG_INFO("Initialised random number generator.");
}


int Random::randint(int min, int max)
{
	// Creates a distribution and returns a number from it
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(m_Rng);
}

double Random::randdouble(double min, double max)
{
	// Creates a distribution and returns a number from it
	std::uniform_real_distribution<> dist(min, max);
	return dist(m_Rng);
}

//####################
//file: misc.h
//Marvin Böttcher (boettcher@evolbio.mpg.de)
//2016
//####################

#ifndef MISC
#define MISC

#include <random>
#include <iostream>

/** share one RNG engine across whole project.
 */
extern std::mt19937_64 rng;

#endif

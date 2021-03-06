#include <cstdlib>
#include <sstream>
#include <string>

#include "random.h"

using namespace std;

#include <iostream>

Random::Random() {
  _randomState = static_cast<unsigned int>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count()
  );
}

string Random::randomIdentifier() {
  int randInt = rand_r(&_randomState);

  ostringstream stringBuilder;
  stringBuilder << hex << randInt;
  return stringBuilder.str();
}

int Random::randomIntWithAverage(int average) {
  float randomFloat = float(rand_r(&_randomState)) / RAND_MAX;
  int val = int(randomFloat * 2 * average);
  return val;
}

int Random::randomIntWithMax(int max) {
  return rand_r(&_randomState) % max;
}

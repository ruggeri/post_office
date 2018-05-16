#ifndef RANDOM_H
#define RANDOM_H

#include <string>

struct Random {
  Random();

  float randomFloat();
  std::string randomIdentifier();
  int randomIntWithAverage(int average);
  int randomIntWithMax(int max);

  private:
    unsigned int _randomState;
};


#endif /* RANDOM_H */

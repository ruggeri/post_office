#include <cstdlib>
#include <sstream>
#include <string>

#include "random.h"

using namespace std;

string randomIdentifier() {
  int randInt = rand();

  ostringstream stringBuilder;
  stringBuilder << hex << randInt;
  return stringBuilder.str();
}

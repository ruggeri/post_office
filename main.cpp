#include <iostream>
#include <sstream>
#include <string>

#include "mailbox.h"

using namespace std;

void waitOnBuffer(Mailbox& mbox) {
  while (true) {
    string msg = mbox.pop();
    cout << msg << endl;
  }
}

int main() {
  Mailbox mbox;
  auto t = thread([&]() { waitOnBuffer(mbox); });

  int messageIdx = 0;
  while (true) {
    ostringstream stringBuilder;
    stringBuilder << "this is my message " << messageIdx << "!";
    string msg = stringBuilder.str();
    mbox.push(msg);
    messageIdx += 1;
  }

  return 0;
}

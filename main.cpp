#include <iostream>
#include <sstream>
#include <string>

#include "mailbox.h"
#include "post_office.h"

using namespace std;

PostOffice globalPostOffice;

void waitOnBuffer(Mailbox& mbox) {
  while (true) {
    string msg = mbox.pop();
    cout << msg << endl;
  }
}

int main() {
  string identifier = globalPostOffice.createMailbox();

  Mailbox& mbox = globalPostOffice.getMailbox(identifier);
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

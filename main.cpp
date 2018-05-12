#include <iostream>
#include <sstream>
#include <string>

#include "mailbox.h"
#include "post_office.h"

using namespace std;

void waitOnBuffer(Mailbox& mbox) {
  while (true) {
    string msg = mbox.pop();
    cout << msg << endl;
  }
}

string buildMessage(int messageIdx) {
  ostringstream stringBuilder;
  stringBuilder << "this is my message " << messageIdx << "!";
  string msg = stringBuilder.str();

  return msg;
}

void runProducerThread(PostOffice& po) {
  auto identifiers = po.mailboxIdentifiers();

  int messageIdx = 0;
  while (true) {
    for (auto identifier : identifiers) {
      Mailbox& mbox = po.getMailbox(identifier);
      string msg = buildMessage(messageIdx);
      mbox.push(msg);

      messageIdx++;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "must give number of threads to use" << endl;
    return 127;
  }

  PostOffice po;

  int numMailboxes = atoi(argv[1]);

  for (int i = 0; i < numMailboxes; i++) {
    Mailbox& mbox = po.createMailbox();
    thread([&]() { waitOnBuffer(mbox); }).detach();
  }

  runProducerThread(po);
  return 0;
}

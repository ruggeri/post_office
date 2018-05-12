#include "mailbox.h"
#include "post_office.h"
#include "random.h"

using namespace std;

Mailbox& PostOffice::createMailbox() {
  string identifier = randomIdentifier();
  Mailbox* mboxPtr = new Mailbox(identifier);
  mboxMap[identifier] = unique_ptr<Mailbox>(mboxPtr);
  return *mboxPtr;
}

Mailbox& PostOffice::getMailbox(string identifier) {
  return *mboxMap[identifier];
}

vector<string> PostOffice::mailboxIdentifiers() {
  vector<string> keys;
  for (auto& pair : mboxMap) {
    keys.push_back(pair.first);
  }

  return keys;
}

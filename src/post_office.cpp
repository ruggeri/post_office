#include "mailbox.h"
#include "post_office.h"
#include "random.h"

using namespace std;

Mailbox& PostOffice::createMailbox() {
  string identifier = randomIdentifier();
  Mailbox* mboxPtr = new Mailbox(identifier);
  _mboxMap[identifier] = unique_ptr<Mailbox>(mboxPtr);
  return *mboxPtr;
}

Mailbox& PostOffice::getMailbox(string identifier) {
  return *_mboxMap[identifier];
}

vector<string> PostOffice::mailboxIdentifiers() {
  vector<string> keys;
  for (auto& pair : _mboxMap) {
    keys.push_back(pair.first);
  }

  return keys;
}

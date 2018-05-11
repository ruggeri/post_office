#include "mailbox.h"
#include "post_office.h"
#include "random.h"

using namespace std;

string PostOffice::createMailbox() {
  string identifier = randomIdentifier();
  mboxMap[identifier] = make_unique<Mailbox>();
  return identifier;
}

Mailbox& PostOffice::getMailbox(string identifier) {
  return *mboxMap[identifier];
}

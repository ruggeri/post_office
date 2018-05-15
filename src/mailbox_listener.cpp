#include "mailbox_listener.h"

#include <fstream>
#include <sstream>

#include "mailbox.h"
#include "post_office.h"

using namespace std;

vector<thread> forkMailboxListeners(PostOffice& po, int numMailboxes) {
  vector<thread> threads;
  for (int i = 0; i < numMailboxes; i++) {
    Mailbox& mbox = po.createMailbox();
    threads.push_back(forkMailboxListener(po, mbox));
  }

  return threads;
}

void runMailboxListener(Mailbox& mbox) {
  stringstream sstream;
  sstream << "./data/" << mbox.identifier;
  string fname = sstream.str();

  ofstream file;
  file.open(fname);
  while (true) {
    string msg = mbox.pop();
    file << msg << endl;
  }
}

thread forkMailboxListener(PostOffice& po, Mailbox& mbox) {
  return thread([&]() {
    runMailboxListener(mbox);
  });
}

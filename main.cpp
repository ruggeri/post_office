#include <chrono>
#include <iostream>
#include <thread>
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

void runProducerThread(PostOffice& po, int sleepMillis) {
  auto identifiers = po.mailboxIdentifiers();

  int messageIdx = 0;
  while (true) {
    auto identifier = identifiers[rand() % identifiers.size()];
    Mailbox& mbox = po.getMailbox(identifier);

    messageIdx++;
    string msg = buildMessage(messageIdx);
    mbox.push(msg);

    this_thread::sleep_for(chrono::milliseconds(sleepMillis));
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << argv[0] << " [numMailboxes] [sleepMillis]" << endl;
    return 127;
  }

  int numMailboxes = atoi(argv[1]);
  int sleepMillis = atoi(argv[2]);

  vector<thread> threads;

  PostOffice po;
  for (int i = 0; i < numMailboxes; i++) {
    Mailbox& mbox = po.createMailbox();
    threads.push_back(thread([&]() { waitOnBuffer(mbox); }));
  }

  for (int i = 0; i < numMailboxes; i++) {
    threads.push_back(thread([&]() {
      runProducerThread(po, sleepMillis);
    }));
  }

  for (auto& t : threads) {
    t.join();
  }

  return 0;
}

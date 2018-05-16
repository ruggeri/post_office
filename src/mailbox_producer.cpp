#include "mailbox_producer.h"

#include <chrono>
#include <cstdlib>
#include <sstream>
#include <thread>

#include "mailbox.h"
#include "post_office.h"

using namespace std;

vector<thread> forkMailboxProducers(
  PostOffice &po, int numThreads, int sleepMillis) {

  vector<thread> threads;
  for (int threadIdx = 0; threadIdx < numThreads; threadIdx++) {
    threads.push_back(forkMailboxProducer(po, sleepMillis));
  }

  return threads;
}

thread forkMailboxProducer(PostOffice &po, int sleepMillis) {
  return thread([&po, sleepMillis]() {
    MailboxProducer mp(po, sleepMillis);
    mp.run();
  });
}

MailboxProducer::MailboxProducer(PostOffice& po, int sleepMillis)
  : _messageIdx(0), _sleepMillis(sleepMillis), _po(po) {
}

string MailboxProducer::nextMessage() {
  ostringstream stringBuilder;
  stringBuilder << "this is my message " << _messageIdx << "!";
  string msg = stringBuilder.str();

  _messageIdx += 1;

  return msg;
}

void MailboxProducer::sleep() {
  int sm = _random.randomIntWithAverage(_sleepMillis);
  this_thread::sleep_for(chrono::milliseconds(sm));
}

void MailboxProducer::run() {
  vector<string> mailboxIdentifiers = _po.mailboxIdentifiers();
  int numMailboxes = mailboxIdentifiers.size();
  while (true) {
    auto identifier = mailboxIdentifiers[_random.randomIntWithMax(numMailboxes)];
    Mailbox& mbox = _po.getMailbox(identifier);

    string msg = nextMessage();
    mbox.push(msg);

    sleep();
  }
}

#include <iostream>
#include <thread>
#include <vector>

#include "mailbox_listener.h"
#include "mailbox_producer.h"
#include "post_office.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << argv[0] << " [numMailboxes] [sleepMillis]" << endl;
    return 127;
  }

  int numMailboxes = atoi(argv[1]);
  int sleepMillis = atoi(argv[2]);

  PostOffice po;
  vector<thread> listenerThreads = forkMailboxListeners(po, numMailboxes);
  vector<thread> producerThreads = forkMailboxProducers(po, numMailboxes, sleepMillis);

  // The point is that these threads will never join.
  for (auto& t : listenerThreads) {
    t.join();
  }

  return 0;
}

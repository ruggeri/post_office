#ifndef __MAILBOX_PRODUCER
#define __MAILBOX_PRODUCER

#include <string>
#include <thread>
#include <vector>

struct PostOffice;

std::vector<std::thread> forkMailboxProducers(
  PostOffice &po, int numThreads, int sleepMillis
);
std::thread forkMailboxProducer(PostOffice &po, int sleepMillis);

class MailboxProducer {
  public:
    MailboxProducer(PostOffice& po, int sleepMillis);

    void run();

  private:
    std::string nextMessage();
    void sleep();

    int _messageIdx;
    int _sleepMillis;
    PostOffice& _po;
};

#endif // __MAILBOX_PRODUCER

#ifndef __MAILBOX_LISTENER
#define __MAILBOX_LISTENER

#include <thread>
#include <vector>

struct Mailbox;
struct PostOffice;

std::vector<std::thread> forkMailboxListeners(
  PostOffice& po, int numMailboxes
);

#endif // __MAILBOX_LISTENER

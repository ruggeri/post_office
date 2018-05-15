#ifndef __MAILBOX_LISTENER
#define __MAILBOX_LISTENER

#include <thread>
#include <vector>

struct Mailbox;
struct PostOffice;

std::vector<std::thread> forkMailboxListeners(
  PostOffice& po, int numMailboxes
);
std::thread forkMailboxListener(PostOffice& po, Mailbox& mbox);

#endif // __MAILBOX_LISTENER

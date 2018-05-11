#ifndef __MAILBOX
#define __MAILBOX

#include <string>
#include <thread>
#include <vector>

struct Mailbox {
  static const int MAX_CAPACITY = 10;

  std::vector<std::string> messages;
  std::mutex m;
  std::condition_variable notEmpty;
  std::condition_variable notFull;

  void push(std::string msg);
  std::string pop();
};

#endif // __MAILBOX

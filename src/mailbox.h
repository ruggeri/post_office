#ifndef MAILBOX
#define MAILBOX

#include <condition_variable>
#include <mutex>
#include <string>
#include <vector>

struct Mailbox {
  static const int MAX_CAPACITY = 10;

  public:
    explicit Mailbox(std::string& identifier);

    std::string identifier();
    std::string pop();
    void push(std::string msg);

  private:
    std::string _identifier;
    std::vector<std::string> _messages;
    std::mutex _mutex;
    std::condition_variable _notEmpty;
    std::condition_variable _notFull;
};

#endif // MAILBOX

#include "mailbox.h"

using namespace std;

void Mailbox::push(string msg) {
  unique_lock<mutex> l(m);

  notFull.wait(l, [this]() {
    return messages.size() < MAX_CAPACITY;
  });

  messages.push_back(msg);
  notEmpty.notify_all();
}

string Mailbox::pop() {
  unique_lock<mutex> l(m);
  notEmpty.wait(l, [this]() {
    return messages.size() > 0;
  });

  string msg = messages.back();
  messages.pop_back();
  notFull.notify_all();
  return msg;
}

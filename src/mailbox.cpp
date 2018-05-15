#include "mailbox.h"

using namespace std;

Mailbox::Mailbox(string& identifier) : _identifier(identifier) {
}

std::string Mailbox::identifier() {
  return _identifier;
}

string Mailbox::pop() {
  unique_lock<mutex> l(_mutex);
  _notEmpty.wait(l, [this]() {
    return _messages.size() > 0;
  });

  string msg = _messages.back();
  _messages.pop_back();
  _notFull.notify_all();
  return msg;
}

void Mailbox::push(string msg) {
  unique_lock<mutex> l(_mutex);

  _notFull.wait(l, [this]() {
    return _messages.size() < MAX_CAPACITY;
  });

  _messages.push_back(msg);
  _notEmpty.notify_all();
}

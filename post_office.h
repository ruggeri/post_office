#ifndef __POST_OFFICE
#define __POST_OFFICE

#include <string>
#include <unordered_map>

struct Mailbox;

struct PostOffice {
  std::unordered_map<std::string, std::unique_ptr<Mailbox>> mboxMap;

  std::string createMailbox();
  Mailbox& getMailbox(std::string identifier);
};

#endif // __POST_OFFICE

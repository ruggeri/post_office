#ifndef __POST_OFFICE
#define __POST_OFFICE

#include <string>
#include <unordered_map>
#include <vector>

struct Mailbox;

struct PostOffice {
  std::unordered_map<std::string, std::unique_ptr<Mailbox>> mboxMap;

  Mailbox& createMailbox();
  Mailbox& getMailbox(std::string identifier);
  std::vector<std::string> mailboxIdentifiers();
};

#endif // __POST_OFFICE

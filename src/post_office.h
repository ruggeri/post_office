#ifndef POST_OFFICE
#define POST_OFFICE

#include <string>
#include <unordered_map>
#include <vector>

// TODO: Wish I didn't have to #include this. Need for destructor?
#include "mailbox.h"
#include "random.h"

struct PostOffice {
  public:
    Mailbox& createMailbox();
    Mailbox& getMailbox(std::string identifier);
    std::vector<std::string> mailboxIdentifiers();

  private:
    std::unordered_map<std::string, std::unique_ptr<Mailbox>> _mboxMap;
    Random _random;
};

#endif // POST_OFFICE

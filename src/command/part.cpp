#include "part.hpp"

namespace irc {

Part::Part() {}
Part::~Part() {}

std::string part(std::string line, User * user, Select *select)
{
    (void)select;
    std::vector<std::string> cmd = irc::ft_split(line, " ");
    (void)user;
    if (cmd.size() < 2)
        return("err");
    //remove user from channel
    //set user channel to null
    // toSend = ":" + nick + "!" + user + "@" + host + " " + buf + EOL;
    return (":"+ user->getNickname() + " PART #lobby\n");
}

} 
#include "part.hpp"

namespace irc {

Part::Part() {
    _name = "PART";
}
Part::~Part() {}

std::string execute(std::string line, User * user, Select *select)
{
    (void)select;
    std::vector<std::string> cmd = irc::ft_split(line, " ");
    (void)user;
    if (cmd.size() < 2)
        return("err");
    //remove user from channel
    //set user channel to null
    // toSend = ":" + nick + "!" + user + "@" + host + " " + buf + EOL;
    return (":"+ user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname()+" PART #lobby " +":"+user->getNickname()+"\r\n");
}

} 
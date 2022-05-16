#include "privmsg.hpp"
#include "select.hpp"

namespace irc {

Privmsg::Privmsg() { _name = "PRIVMSG";}
Privmsg::~Privmsg() {}

std::string	Privmsg::execute(std::string line, User * user, Select &select) {
    std::string msg;
    (void)user;
    (void)select;

    msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
    return msg;
}
} 
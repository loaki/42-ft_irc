#include "privmsg.hpp"
#include "select.hpp"

namespace irc {

Privmsg::Privmsg() { _name = "PRIVMSG";}
Privmsg::~Privmsg() {}

std::string	Privmsg::execute(std::string line, User * user, Select &select) {
    std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
	std::string channelname = v_cmd[1];

    msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
 	std::vector<User *> users = select.getUsersInchannel(channelname);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getUserFd() != user->getUserFd())
			select.sendReply(msg, *(*it));
	}
    return msg;
}
} 
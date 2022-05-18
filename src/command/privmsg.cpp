#include "privmsg.hpp"
#include "select.hpp"

namespace irc {

Privmsg::Privmsg() { _name = "PRIVMSG";}
Privmsg::~Privmsg() {}

std::string	Privmsg::execute(std::string line, User * user, Select &select) {
    std::string msg;
	// int ret = -1;

    msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
	std::vector<User *> users = select.getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*it)->getUserFd() != user->getUserFd())
			select.sendReply(msg, (*it));
			// ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);

	}
	// if (ret == SYSCALL_ERR) {
	// 	std::cout << "[Send response failed]" << std::endl;
	// 	select.clientDisconn(user->getUserFd());
	// 	return "";
	// }
    return msg;
}
} 
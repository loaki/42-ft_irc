#include "part.hpp"

namespace irc {

Part::Part() {
    _name = "PART";
}
Part::~Part() {}

std::string	Part::execute(std::string line, User *user, Select &select)
{
    (void)select;
    std::vector<std::string> cmd = irc::ft_split(line, " ");
    (void)user;
	int ret = -1;

    if (cmd.size() < 2)
    {    return("err");}
    //remove user from channel
    //set user channel to null
    // toSend = ":" + nick + "!" + user + "@" + host + " " + buf + EOL;
	std::string msg = ":"+ user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " "+line+" " + ":" + user->getNickname() + "\r\n";
	ret = send(user->getUserFd(), msg.c_str(), msg.length(), 0);
	if (ret == SYSCALL_ERR) {
		std::cout << "[Send response failed]" << std::endl;
		select.clientDisconn(user->getUserFd());
		return NULL;
	}
	return msg;
}

} 
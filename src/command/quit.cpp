#include "quit.hpp"

namespace irc {

Quit::Quit() {
    _name = "QUIT";
}
Quit::~Quit() {}

std::string	Quit::execute(std::string line, User *user, Select &select)
{
    (void)select;
    std::vector<std::string> v_cmd = irc::ft_split(line, " ");
    (void)user;

    if (v_cmd.size() < 2)
    {    return("err");}
	std::string channelname = v_cmd[1];

	std::string msg = user->getPrefix() + "QUIT" + " :Quit: leaving" + "\r\n";
	std::vector<User *> users = select.getUsersInchannel(channelname);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		select.sendReply(msg, *(*it));
	}
	select.getChannelByName(channelname)->removeUser(user);
	select.clientDisconn(user->getUserFd());
	return msg;
}

} 
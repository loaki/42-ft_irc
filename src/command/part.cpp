#include "part.hpp"

namespace irc {

Part::Part() {
    _name = "PART";
}
Part::~Part() {}

std::string	Part::execute(std::string line, User *user, Select &select)
{
    (void)select;
    std::vector<std::string> v_cmd = irc::ft_split(line, " ");
    (void)user;
	int ret = -1;

    if (v_cmd.size() < 2)
    {    return("err");}
	std::string channelname = v_cmd[1];

    //remove user from channel
    //set user channel to null
    // toSend = ":" + nick + "!" + user + "@" + host + " " + buf + EOL;

	// std::vector<User *> users = select.getUsersInchannel(channelname);
	// for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
	std::string msg = user->getPrefix() + " " + line + " " + ":" + user->getNickname() + "\r\n";
	std::vector<User *> users = select.getUsersInchannel(channelname);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		// select.sendReply(msg, *(*it));
		ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
		if (ret == SYSCALL_ERR) {
			std::cout << "[Send response failed]" << std::endl;
			select.clientDisconn((*it)->getUserFd());
			return NULL;
		}
	}
	select.getChannelByName(channelname)->removeUser(user);

	return msg;
}

} 
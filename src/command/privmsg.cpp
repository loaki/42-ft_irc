#include "privmsg.hpp"
#include "select.hpp"

namespace irc
{

	Privmsg::Privmsg() { _name = "PRIVMSG"; }
	Privmsg::~Privmsg() {}

	std::string Privmsg::execute(std::string line, User *user, Select &select)
	{
		std::string msg;
		std::vector<std::string> v_cmd = ft_split(line, " ");
		std::string channelname = v_cmd[1];

		msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
		std::vector<User *> users = select.getUsersInchannel(channelname);
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		{
			if ((*it)->getUserFd() != user->getUserFd())
			{
				int ret = -1;

				ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
				std::cout << "ret :" << ret << "\nmsg :" << msg << std::endl;
				if (ret == SYSCALL_ERR)
				{
					std::cout << "[Send response failed]" << std::endl;
					select.clientDisconn((*it)->getUserFd());
					return NULL;
				}
				if ((*it)->getUserFd() == select.botFD) {

					std::string msgR = ":" + (*it)->getNickname() + "!" + (*it)->getUsername() + "@" + (*it)->getHostname() + " " + "** TAAAK JE SUIS UN ROBOT **" + "\r\n";
					ret = send (user->getUserFd(), msgR.c_str(), msgR.length(), 0);
					std::cout << "ROBOT ret :" << ret << "\nmsg :" << msg << std::endl;

				}
			}
			// select.sendReply(msg, *(*it));
		}
		return msg;
	}
}

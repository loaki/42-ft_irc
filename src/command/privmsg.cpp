#include "privmsg.hpp"
#include "select.hpp"

namespace irc
{

	Privmsg::Privmsg() { _name = "PRIVMSG"; }
	Privmsg::~Privmsg() {}

	std::string Privmsg::botResponse(std::string msg)
	{
		const char * h[] = {":hello", ":hi", ":salut", ":hola", "yo", ":bonjour", ":bonsoir"};
		std::vector<std::string> hello(h, h+7);
		for (std::vector<std::string>::iterator it = hello.begin(); it != hello.end(); it++)
		{
			if (*it == msg)
				return("H.I. Bzzz");
		}
		const char * q[] = {":what", ":how", ":are", ":do", ":est", ":quel", ":quelle", ":comment"};
		std::vector<std::string> quest(q, q+8);
		for (std::vector<std::string>::iterator it = quest.begin(); it != quest.end(); it++)
		{
			if (*it == msg)
				return("Stop asking stupid questions. Beep Boop");
		}
		return ("");
	}

	std::string Privmsg::execute(std::string line, User *user, Select &select)
	{
		std::string msg;
		std::vector<std::string> v_cmd = ft_split(line, " ");
		std::string channelname = v_cmd[1];

		msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
		std::vector<User *> users = select.getUsersInchannel(channelname);
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		{
			int ret = -1;
			std::cout<<v_cmd[2]<<std::endl;
			msg = botResponse(v_cmd[2]);
			if(channelname == "#botchan" && msg !="")
			{
				std::string msgR = ":MRrobot!robot@127.0.0.1 PRIVMSG #botchan :** "+msg+" **\r\n";
				ret = send (user->getUserFd(), msgR.c_str(), msgR.length(), 0);
			}
			if ((*it)->getUserFd() != user->getUserFd())
			{
				int ret = -1;

				ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
				//std::cout << "ret :" << ret << "\nmsg :" << msg << std::endl;
				if (ret == SYSCALL_ERR)
				{
					std::cout << "[Send response failed]" << std::endl;
					select.clientDisconn((*it)->getUserFd());
					return NULL;
				}
			}
			// select.sendReply(msg, *(*it));
		}
		return msg;
	}
}

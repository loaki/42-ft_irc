#include "privmsg.hpp"
#include "select.hpp"

namespace irc
{

	Privmsg::Privmsg() { _name = "PRIVMSG"; }
	Privmsg::~Privmsg() {}

	std::string Privmsg::botResponse(std::string msg)
	{
		const char * h[] = {"hello", "hi", "salut", "hola", "yo", "bonjour", "bonsoir"};
		std::vector<std::string> hello(h, h+7);
		std::vector<std::string> msgSplit = ft_split(msg, ":");
		std::cout<<msgSplit[1];
		for (std::vector<std::string>::iterator it = hello.begin(); it != hello.end(); it++)
		{
			if (msgSplit[1].find(*it) != std::string::npos)
				return("H.I. Bzzz");
		}
		if (msgSplit[1].find('?') != std::string::npos ) {
			std::replace(msgSplit[1].begin(), msgSplit[1].end(), '?', ' ');
			std::replace(msgSplit[1].begin(), msgSplit[1].end(), ' ', '+');
			return ("https://www.google.fr/search?q="+ msgSplit[1]);
		}
		if (msgSplit[1].find("transfer" )!= std::string::npos) {
			return ("https://unsplash.com/photos/odxB5oIG_iA/download?ixid=MnwxMjA3fDB8MXxzZWFyY2h8MXx8ZnJlZXxlbnwwfHx8fDE2NTM0ODE4NDc&force=true");
		}
		return("");
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
			std::string msgR = botResponse(line);
			if((*it)->getUserFd() == user->getUserFd() && channelname == "#botchan" && msgR !="")
			{
				msgR = ":MRrobot!robot@127.0.0.1 PRIVMSG #botchan :** "+msgR+" **\r\n";
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

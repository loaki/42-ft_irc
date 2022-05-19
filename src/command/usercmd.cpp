#include "usercmd.hpp"

namespace irc {

Usercmd::Usercmd(){
	_name = "USER";
}

Usercmd::~Usercmd(){}

std::string Usercmd::execute(std::string line, User *user, Select &select){
	std::string msg;

	std::vector<std::string> v_cmd = ft_split(line, " ");
	if (v_cmd.size() != 4) {
		std::string cmd = "USER";
		msg = ERR_NEEDMOREPARAMS(cmd) + delimiter;
		select.sendReply(msg, user);
		return msg;
	}
	if (user->getJoinServer() == true) {
		msg = ERR_ALREADYREGISTRED();
		msg += delimiter;
		select.sendReply(msg, user);
		return msg;
	}
	user->setUsername(v_cmd[1]);
	user->setHostname(v_cmd[2]);
	return msg;
}



}
//USER <username> <hostname> <servername> <realname>
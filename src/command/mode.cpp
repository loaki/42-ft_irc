#include "mode.hpp"

namespace irc {


Mode::Mode(){ _name = "MODE"; }
Mode::~Mode() {}

Channel *Mode::getChannel(std::string name, Select &select){
		std::vector<Channel *> channel = select.getAllChannel();
		std::vector<Channel *>::iterator it = channel.begin();
		for(; it != channel.end(); it++) {
			if((*it)->getChannelName() == name)
				return *it;
		}
		return NULL;
}

bool Mode::isAdmin(Select &select, std::string chan, std::string nickname) {
	Channel *channel = getChannel(chan, select);
	std::vector<User *> users = channel->getUsers();
	if ((users.front())->getNickname() == nickname) { // is admin; 
		return true;
	}
	return false;
}


std::string Mode::execute(std::string line, User *user, Select &select){
	std::string msg;
	// MODE #b +b xueming_ 
	std::vector<std::string> v_cmd = ft_split(line, " ");
	if (v_cmd.size() == 4 && v_cmd[2] == "+b") {
		std::string chan = v_cmd[1];
		std::string ban = v_cmd[3];
		std::vector<std::string> x = ft_split(ban, "@");
		ban = x[0] + "@" + user->getHostname();

		//:prefix 482 not operator
		if (isAdmin(select, chan, user->getNickname()) == false) {
			msg = user->getPrefix();
			msg += ERR_CHANOPRIVSNEEDED(chan) + delimiter;
			select.sendReply(msg, *user);
			return msg;
		}
		User *banUser = select.getUserInVec(v_cmd[3]);
		// alredy ban
		if (banUser != NULL && banUser->isBan(chan) == true) {
			msg += user->getPrefix();
			msg += " 697 " + user->getNickname() + " " + chan + " " + ban + " b " + " :";
			msg += "Channel " + chan + " list already contains " + ban + delimiter;
			select.sendReply(msg, *user);
			return msg;
		}
		
		// to user admin
		std::vector<User *> users = select.getUsersInchannel(v_cmd[1]);
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
			msg = user->getPrefix();
			msg += " " + v_cmd[0] + " " + v_cmd[1] + " " + v_cmd[2] + " " + ban + delimiter;
			select.sendReply(msg, *(*it));
		}
		if (banUser != NULL && isAdmin(select, chan, ban) == false) {  //is admin not send 
			banUser->setBanList(chan);
			select.sendReply(msg, *banUser);
		}
		return msg;
	}
	else if (v_cmd.size() == 4 && v_cmd[2] == "-b") {
		std::string chan = v_cmd[1];
		std::string ban = v_cmd[3];
		std::vector<std::string> x = ft_split(ban, "@");
		ban = x[0] + "@" + user->getHostname();

		//:prefix 482 not operator
		if (isAdmin(select, chan, user->getNickname()) == false) {
			msg = user->getPrefix();
			msg += ERR_CHANOPRIVSNEEDED(chan) + delimiter;
			select.sendReply(msg, *user);
			return msg;
		}
		User *banUser = select.getUserInVec(v_cmd[3]);
		
		// to user admin
		if (banUser != NULL && isAdmin(select, chan, ban) == false) {  //is admin not send 
			banUser->unsetBanList(chan);
			select.sendReply(msg, *banUser);
		}
		return msg;
	}
	return msg;

}






}
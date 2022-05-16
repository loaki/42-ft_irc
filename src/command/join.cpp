#include "join.hpp"

namespace irc{

Join::Join(){
	 _name = "JOIN";
}
Join:: ~Join(){}

bool Join::ChannelExist(std::string name, std::vector<Channel *> channels){
	std::vector<Channel *>::iterator it = channels.begin();
	for(; it != channels.end(); it++) {
		if ((*it)->getChannelName() == name) 
			return true;
	}
	return false;
}

void Join::leaveAllChannels(){

}

std::string Join::execute(std::string line, User *user, Select &select){
	std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
	std::string channelname = v_cmd[1];

	if(v_cmd.size == 0) {
		msg = ERR_NEEDMOREPARAMS("JOIN");
		msg += delimiter;
		return msg;
	}
	if (v_cmd[1] == "0") {
		leaveAllChannels();
	}
	msg = RPL_TOPIC(channelname, select.getAllChannel.);
	return msg;
	
}


/*If a JOIN is successful,(using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.*/

}
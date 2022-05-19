#include "list.hpp"

namespace irc {

List::List(){
	_name = "LIST";
}
List:: ~List(){}

std::string List::execute(std::string line, User *user, Select &select){
	std::string msg;
	std::vector<std::string> v_cmd = ft_split(line, " ");
	//channel 
	std::vector<Channel *> channels = select.getAllChannel();
	if (channels.empty()) {
		return "Error: not channel;";
	}
	else {
		std::vector<Channel *>::iterator it = channels.begin();
		for(; it != channels.end(); it++) {
			msg = user->getPrefix();
			msg += RPL_LIST((*it)->getChannelName(), std::to_string((*it)->getUsers().size()));
			msg += delimiter;
			select.sendReply(msg, *user);

			msg.clear();
			msg = user->getPrefix();
			msg += RPL_LISTEND();
			msg += delimiter;
			select.sendReply(msg, *user);
		}
	}
	return msg;
}


}
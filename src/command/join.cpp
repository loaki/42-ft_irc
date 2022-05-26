#include "join.hpp"

namespace irc{

Join::Join(){
	 _name = "JOIN";
}
Join:: ~Join(){}

bool Join::ChannelExist(std::string name, std::vector<Channel *> channels){
	std::vector<Channel *>::iterator it = channels.begin();
	for(; it != channels.end(); it++) {
		if ((*(*it)).getChannelName() == name) 
			return true;
	}
	return false;
}

std::string Join::execute(std::string line, User *user, Select &select){
	std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
	std::string channelname = v_cmd[1];

	if(v_cmd.size() == 0) {
		msg += delimiter;
		return msg;
	}

	if (user->isBan(channelname) == true) {
		msg = user->getPrefix();
		std::string ban = user->getNickname();
		msg += ERR_BANNEDFROMCHAN(channelname, ban);
		msg += delimiter;
		select.sendReply(msg, *user);
		return msg;
	} 

	std::string listname = "";
 	std::vector<Channel *> channels = select.getAllChannel();
	if (select.getChannelByName(channelname) == NULL){
		select.addChannel(channelname);
	}
	channels = select.getAllChannel();
	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*(*it)).getChannelName() == channelname)
		{
			if ((*(*it)).getUserInchannel(user->getNickname()) == NULL)
				(*(*it)).addUser(user);
			std::vector<User *> chanUsers = (*(*it)).getUsers();
			for (std::vector<User*>::iterator it2 = chanUsers.begin(); it2 < chanUsers.end(); it2++)
			{
				listname += (*(*it2)).getNickname();
				if ((it2) == (chanUsers.end() - 1))
					break;
				listname += " ";
			}
		}
	}
	std::string msgself1 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 353 " + user->getNickname() +" = "+ channelname + " : @" + listname + "\r\n";
	std::string msgself2 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 366 " + user->getNickname() +" "+ channelname + " :End of /NAMES list"+"\r\n";
	msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
 	std::vector<User *> users = select.getUsersInchannel(channelname);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {

		if ((*(*it)).getUserFd() != user->getUserFd())
		{
			select.sendReply(msg, *(*it));
		}
		else
		{
			select.sendReply(msg, *(*it));
			select.sendReply(msgself1, *(*it));
			select.sendReply(msgself2, *(*it));
		}
	}
	return msg;
	
}

}
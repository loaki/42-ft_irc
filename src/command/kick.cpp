#include "kick.hpp"

namespace irc
{
	Kick::Kick(){
		_name = "KICK";
	}
	Kick::~Kick(){}

	bool Kick::isChannel(std::string name, Select &select){
		std::vector<Channel *> channel = select.getAllChannel();
		std::vector<Channel *>::iterator it = channel.begin();
		for(; it != channel.end(); it++) {
			if((*it)->getChannelName() == name)
				return true;
		}
		return false;
	}


	Channel *Kick::getChannel(std::string name, Select &select){
		std::vector<Channel *> channel = select.getAllChannel();
		std::vector<Channel *>::iterator it = channel.begin();
		for(; it != channel.end(); it++) {
			if((*it)->getChannelName() == name)
				return *it;
		}
		return nullptr;
	}

	bool Kick::userInChannel(std::string channelname, std::string name, Select &select){
		Channel *Channel = select.getChannelByName(channelname);
		if (Channel != NULL) {
			if (Channel->isUser(name) == true)
				return true;
		}
		return false;
	}

	bool Kick::checkChannelName(std::string channelname) {
		Channel *Channel = NULL; 
		return (Channel->isChannelName(channelname)); 
	}

	std::string  Kick::execute(std::string line, User *user, Select &select){
		std::string msg = user->getPrefix();

		//KICK &Melbourne Matthew :  size = 4
		std::vector<std::string> v_cmd = ft_split(line, " ");
		std::string channelname = v_cmd[1];
		std::string nickname = v_cmd[2];

		std::cout << v_cmd.size() << std::endl;

		if (v_cmd.size() != 4) {
			std::string cmd = "KICK";
			msg += ERR_NEEDMOREPARAMS(cmd) + delimiter;  // no params
			select.sendReply(msg, *user);
			return msg;
		}

		//prefix  401 xuwang_ newnick :No such nick
		if (select.userInVec(nickname) == false) {
			msg += ERR_NOSUCHNICK(user->getNickname(), nickname) + delimiter;
			select.sendReply(msg, *user);
			return msg;
		}

		if (checkChannelName(channelname) == false) {
			msg += ERR_BADCHANMASK(channelname) + delimiter; //channel name wrong
			select.sendReply(msg, *user);
			return msg;
		}

		if (isChannel(channelname, select) == false) {
		 	msg += ERR_NOSUCHCHANNEL(channelname) + delimiter;  //no channel
			select.sendReply(msg, *user);
			return msg;
		}

		if (userInChannel(channelname, nickname, select) == false) {
			msg += ERR_USERNOTINCHANNEL(nickname, channelname) + delimiter; //no user in channel
			select.sendReply(msg, *user);
			return msg;
		}

		
		Channel *channel = getChannel(channelname, select);
		// if (channel->getAdmin()->getNickname() != user->getNickname()) { // not admin; 
		// 	msg += ERR_CHANOPRIVSNEEDED(channelname) + delimiter;
		// 	select.sendReply(msg, *user);
		// 	return msg;
		// }

		std::cout << "channel name: " << channel->getChannelName() << std::endl;
		std::vector<User *> users = channel->getUsers();
		std::vector<User *>::iterator it = users.begin();
		std::vector<User *>::iterator ite = users.end();
		for(; it!=ite; it++)
			std::cout << "user in channel: " <<  (*it)->getNickname() << std::endl;

		// to user admin :xueming!xuwang@127.0.0.1 KICK #aa xueming_ xueming
		User *removeUser = channel->getUserInchannel(nickname);
		channel->removeUser(removeUser);
		msg += " KICK " + channelname + " " + nickname + " " + user->getNickname() + delimiter;
		//to user remouve
		if (removeUser != nullptr)
			select.sendReply(msg, *removeUser);
		//to admin
		select.sendReply(msg, *user);
		return msg;
	}





} // namespace irc

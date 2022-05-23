#include "channel.hpp"

#define CHANNEL_MAX_NAME 50

namespace irc {

Channel::Channel(std::string channelname, User *admin):_admin(admin){
	this->setChannelName(channelname);
}

Channel::Channel(std::string channelname):_channelName(channelname){}

User 	*Channel::getAdmin() {return this->_admin;}

Channel::Channel(){}

Channel::~Channel(){
}

std::vector<User *>	Channel::getUsers(){ return this->_users;}

 std::string        Channel:: getChannelName(){ return this->_channelName;}

 std::string         Channel:: getTopic(){return this->_topic;}

void	Channel::setChannelName(std::string name){ 
	this->_channelName = name.substr(1, CHANNEL_MAX_NAME);
}

User*	Channel::getUserInchannel(std::string name){
	std::vector<User *>::iterator it = this->_users.begin();
	for(; it != this->_users.end(); it++) {
		if((*it)->getNickname() == name)
			return *it;
	}
	return NULL;
}

User*	Channel::getUserInchannel(int fd){
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();
	for(;it != ite; it++) {
		if((*it)->getUserFd() == fd)
			return *it;
	}
	return NULL;
}

void	Channel::addUser(User *user){
	this->_users.push_back(user);
}

void	Channel::removeUser(User *user){
	std::vector<User *>::iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) {
		if ((*it)->getUserFd() == user->getUserFd()) {
			// std::cout<<"removed\n";
			this->_users.erase(it);
			return ;
		}
	}
}


// void	Channel::printAllUsers(){
// 	std::vector<User *>::const_iterator it = this->_users.begin();
// 	for (; it != this->_users.end(); it++) 
// 		//std::cout << "nickname: " << (*it)->getNickname() << " fd: " << (*it)->getUserFd() << std::endl;
// }

bool	Channel::isUser(User *user){
	std::vector<User *>::const_iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) {
		if ((*it)->getUserFd() == user->getUserFd())
			return true;
	}
	return false;
}
bool	Channel::isUser(std::string name){
	std::vector<User *>::const_iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) {
		if ((*it)->getNickname() == name)
			return true;
	}
	return false;
}

void	Channel::MsgToUser(User* user, std::string message){
	send(user->getUserFd(), message.c_str(), message.length(), 0);
}

bool	Channel::isChannelName(std::string channelName) {
	if (channelName.empty() || channelName.size() > 50) 
		return false;
	if (channelName[0] != '#' && channelName[0] != '&') 
		return false;

	for (size_t i = 0; i < channelName.size(); i++) {
		if (channelName[i] == ' ' || channelName[i] == 7 || channelName[i] == ',')
			return false;
	}
	return true;
}

}
#include "channel.hpp"

namespace irc {

Channel::Channel(): _channelName(), _users(){}

Channel::Channel(std::string channelname):_channelName(channelname){}

Channel::~Channel(){
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this-> _users.end();
	for(; it != ite; it++) 
		delete *it;
	this->_users.clear();
}

std::vector<User *>	Channel::getUsers(){ return this->_users;}

 std::string        Channel:: getChannelName(){ return this->_channelName;}

 std::string         Channel:: getTopic(){return this->_topic;}

void	Channel::setChannelName(std::string name){ this->_channelName = name;}

User*	Channel::getUserInchannel(std::string name){
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this-> _users.end();
	for(; it != ite; it++) {
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
	return nullptr;
}

void	Channel::addUser(User *user){
	this->_users.push_back(user);
}

void	Channel::removeUser(User *user){
	std::vector<User *>::iterator it = this->_users.begin();
	for (; it < this->_users.end(); it++) {
		if ((*it) == user) {
			this->_users.erase(it);
			break;
		}
	}
}

void	Channel::printAllUsers(){
	std::vector<User *>::const_iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) 
		std::cout << "nickname: " << (*it)->getNickname() << " fd: " << (*it)->getUserFd() << std::endl;
}

bool	Channel::isUser(User *user){
	std::vector<User *>::const_iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++) {
		if (*it == user)
			return true;
	}
	return false;
}

void	Channel::MsgToUser(User* user, std::string message){
	send(user->getUserFd(), message.c_str(), message.length(), 0);
}



// void	Channel::MsgToAChannel(std::string message){

// }


}
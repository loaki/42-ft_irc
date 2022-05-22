#include "user.hpp"

namespace irc {

User::User(int fd): _fd(fd), _nickname(), _username(), _chunk(true) {
}

User::~User(){}

void User::setName(std::vector<std::string> Buff) {

	for (std::vector<std::string>::iterator it = Buff.begin(); it != Buff.end(); it++) {
		if ((*it).find("USER") != std::string::npos) 
		{
			std::string temp = (*it).substr(5);
			int end = temp.find(" ");
			std::cout << "User name: " << temp.substr(0, end) << std::endl;
			this->setUsername(temp.substr(0, end));
		}
	}
}

std::string			User::getPrefix(){
	std::string prefix;

	prefix += ":";
	prefix += this->_nickname;
	prefix += "!";
	prefix += this->_username;
	prefix += "@";
	prefix += this->_hostname;
	return prefix;
}

void User::setNickname(std::string name){
	this->_nickname = name;
}

void User::setUsername(std::string name){
	this->_username = name;
}

void User::setHostname(std::string hostname){
	this->_hostname = hostname;
}

void User::setPass(std::string pass){
	this->_pass = pass;
}

void User::setUserFd(int fd){
	this->_fd = fd;
}

void	User::setChunk(bool chunk) {
	this->_chunk = chunk;
}

void User::setJoinServer(bool join) {
	this->_joinServer = join;
}

bool User::getJoinServer(){ return this->_joinServer;}

std::string const& User::getNickname()const{return this->_nickname;}

std::string const& User::getUsername()const{ return this->_username;}

std::string const& User::getHostname()const{ return this->_hostname;}

std::string const& User::getPass()const{ return this->_pass;}

bool const&	User::getChunk()const { return this->_chunk; }

int const& User::getUserFd()const {return this->_fd;}


}

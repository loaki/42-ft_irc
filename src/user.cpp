#include "user.hpp"

namespace irc {

User::User(int fd): _fd(fd), _nickname(), _username(){}

User::~User(){}

void		User::setId(std::vector<User *> users) {

	this->_id.first = 0;
	for (size_t i = 0; i < users.size(); i++) {
		if (users.size() == 1) break;
		if (users[i]->_id.first == this->_id.first){
			this->_id.first = i;
			continue;
		}
	}
	this->_id.second = 0;
	// this->_id.second = craftId();
	// for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
	// 	if ((this->getUserId().second == (*(*it)).getUserId().second) && this != (*it)) {
	// 		this->_id.second = craftId();
	// 		it = users.begin();
	// 	}
	// }
	// std::cout << "This is user id first: " << (*this)._id.first << std::endl;
	// std::cout << "This is user id second: " << (*this)._id.second << std::endl;

}

// std::string		User::craftId() {
// 	std::string s;

// 	static const char alphanum[] =
// 			"0123456789"
// 			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// 			"abcdefghijklmnopqrstuvwxyz";
// 	srand( time( 0 ) );
// 	for (int i = 0; i < 10; ++i) {
// 		s += alphanum[rand() % (sizeof(alphanum) - 1)];
// 	}
// 	return (s);
// }

void			User::setName(std::vector<std::string> Buff) {

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

void User::setUserFd(int fd){
	this->_fd = fd;
}

void User::setJoinServer(bool join) {
	this->_joinServer = join;
}

bool User::getJoinServer(){ return this->_joinServer;}

std::string const& User::getNickname()const{return this->_nickname;}

std::string const& User::getUsername()const{ return this->_username;}

std::string const& User::getHostname()const{ return this->_hostname;}

int const& User::getUserFd()const {return this->_fd;}

std::pair<size_t, int> const& User::getUserId()const {return this->_id;}





}

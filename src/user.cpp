#include "user.hpp"

namespace irc {

User::User(int fd): _fd(fd), _nickname(), _username(){}
User::~User(){}

void User::setNickname(std::string name){this->_nickname = name;}
void User::setUsername(std::string name){this->_username = name;}
void User::setUserFd(int fd){this->_fd = fd;}

std::string const& User::getNickename()const{return this->_nickname;}
std::string const& User::getUsername()const{ return this->_username;}
int const& User::getUserFd()const {return this->_fd;}


}

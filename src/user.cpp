#include "user.hpp"

namespace irc {

User::User(int fd): _fd(fd), _nickname(), _username(){}

User::~User(){}

void User::setNickname(std::string name){this->_nickname = name;}

void User::setUsername(std::string name){this->_username = name;}

void User::setUserFd(int fd){this->_fd = fd;}

void User::setUserId(std::string id){this->_id = id;}

void User::setHostname(std::string hostname){this->_hostname = hostname;}

std::string const& User::getNickname()const{return this->_nickname;}

std::string const& User::getUsername()const{ return this->_username;}

std::string const& User::getHostname()const{ return this->_hostname;}

int const& User::getUserFd()const {return this->_fd;}

std::string const& User::getUserId()const {return this->_id;}

void User::setJoinServer(bool join) {this->_joinServer = join;}



}

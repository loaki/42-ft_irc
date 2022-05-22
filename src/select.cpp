#include "select.hpp"

namespace irc {

// public: class init
Select::Select():_serverSocket(), users(), clientfds(), mainSet(), rSet(),wSet() {}
Select::Select(Select const& src) { *this = src; }
Select::~Select() {
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	for(; it != ite; it++)
		delete(*it);
	this->users.clear();

	std::vector<Channel *>::iterator cit = this->_channels.begin();
	std::vector<Channel *>::iterator cite = this->_channels.end();
	for(; cit != cite; it++)
		delete(*cit);
	this->_channels.clear();
}

Select& Select::operator=(Select const& rhs) {
	if (this == &rhs) return *this;
	this->_serverSocket = rhs._serverSocket;
	this->users = rhs.users;
	this->clientfds = rhs.clientfds;
	this->mainSet = rhs.mainSet;
	this->rSet = rhs.mainSet;
	this->wSet = rhs.wSet;
	return *this;
}

std::vector<User *> Select::getUsers(){return this->users;}
 std::vector<Channel *> Select::getAllChannel() {return this->_channels;}
 
// public: serveur creat 
void    Select::serverStart(const short& port, const std::string&  password) {
	this->_serverSocket.createServer(port, password);

	FD_ZERO(&this->mainSet); 
	FD_SET(this->_serverSocket.getServerFd(), &this->mainSet);//SET servfd to mainset

	for(;;) {
		this->rSet = this->mainSet;
		int event = select(this->max_fd() + 1, &this->rSet, NULL, NULL, NULL);
		if (event < 0) {
			//return;
			continue ;
		}
		for (int fd = 0; fd <= this->max_fd(); fd++) {
			if (FD_ISSET(fd, &this->rSet)) {    // which fd event
				if (fd == this->_serverSocket.getServerFd()) { //connect:new client connect 
					this->clientConn();
					break ;
				}
				else {                     //recv
					this->handleReq(fd);
					continue;
				}
			}
		}
	}
}

// private: get max fd
int    Select::max_fd() {
	int max = this->_serverSocket.getServerFd();
	if (this->clientfds.empty())
		return max;
	
	for (std::vector<int>::iterator it = this->clientfds.begin(); it != this->clientfds.end(); it++) {
		if (*it > max)
			max = *it;
	}
	return max;
}

void    Select::clientConn() { //get client fd  
	int                 clientConnFd = -1;
	struct sockaddr_in	clientAddr;
	socklen_t			len = sizeof(clientAddr);

	clientConnFd = accept(this->_serverSocket.getServerFd(), (struct sockaddr *)&clientAddr, &len);
	if (clientConnFd == SYSCALL_ERR)
		exitFailure("accept failed");

	User *newuser = new User(clientConnFd);
	newuser->setNickname("");
	newuser->setHostname(std::string(inet_ntoa(clientAddr.sin_addr)));
	newuser->setJoinServer(false);
	this->users.push_back(newuser);// add new user
	this->clientfds.push_back(clientConnFd); //add new fd
	FD_SET(clientConnFd, &this->mainSet);  //add new clientfd to mainset
}

//delete one clientfd
void    Select::clientDisconn(const int clientFd) {
	close(clientFd);
	FD_CLR(clientFd, &this->mainSet);   //delete fd of mainset

	// std::vector<int>::iterator it = this->clientfds.begin();
	for (std::vector<int>::iterator it = clientfds.begin(); it != clientfds.end(); it++) {
		if (*it == clientFd)
		{
			clientfds.erase(it);
			break ;}
	}
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((*(*it)).getUserFd() == clientFd)
		{
			delete (*it);
			users.erase(it);
			break ;
		}
	}
}

std::vector<std::string> Select::configBuff() {
	std::vector<std::string> vecBuff;
	std::string buf = this->buff;
	vecBuff = ft_split(buf, "\r\n");
	return vecBuff;
}

bool Select::PasswordConnect(std::vector<std::string> buff){
	size_t pos = 0;
	std::vector<std::string>::iterator it = buff.begin();
	for(;it != buff.end(); it++){
		if ((*it).find("PASS") != std::string::npos) {
			pos = (*it).find("PASS");
			std::string password = (*it).substr(5);
			if (password == this->_serverSocket.getPassword()){
				return true;
			}
		}
	}
	return false;
}

void Select::addChannel(std::string channelName) { 

	_channels.push_back(new Channel(channelName));
}

void		Select::addNewUsr(std::vector<User *> users, std::vector<std::string> Buff) {

	std::string nick; 
	std::vector<std::string>::iterator it = Buff.begin();
	
	for(; it != Buff.end(); it++) {
		if ((*it).find("NICK") != std::string::npos) 
		{
			nick = (*it).substr(5);
			for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
				if ((*it)->getNickname() == nick) {
					// nick = nick+'_';
					// it = users.begin();
					std::string msg = ":";
					msg += ERR_NICKNAMEINUSE(nick);
					std::cout << "MESSAGE USER FALSE: " << msg << std::endl;
					send(0, msg.c_str(), msg.length(), 0) ;
				}
			}
			users.back()->setNickname(nick);
		}
	}
	(users.back())->setName(Buff);
}

void Select::sendReply(std::string msg, User &user){
	int ret = -1;

	ret = send(user.getUserFd(), msg.c_str(), msg.length(), 0);
	if (ret == SYSCALL_ERR) {
		std::cout << "[Send response failed]" << std::endl;
		this->clientDisconn(user.getUserFd());
		return;
	}
}

Channel * Select::getChannelByName(std::string name){
	// std::vector<Channel *>::iterator it = this->_channels.begin();
	for(std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if((*it)->getChannelName() == name)
			return (*it);
	}
	return NULL;
}


std::vector<User *> Select::getUsersInchannel(std::string name){
	std::vector<Channel *>::iterator it = this->_channels.begin();
	std::vector<User *> users;
	for(; it != this->_channels.end(); it++) {
		if((*it)->getChannelName() == name)
			return ((*it)->getUsers());
	}
	return users;
}

bool Select::userInVec(std::string name) {
	std::vector<User *>::iterator it = users.begin();
		for(; it != users.end(); it++) {
			if ((*it)->getNickname() == name)
				return true;
		}
	return false;
}

void    Select::handleReq(const int fd) {
	int	ret = -1;
	// std::string s(this->buff);

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);   //recv message form clientfd
	// std::cout << fd << std::endl;

	std::cout << "\n ### client : \n" << this->buff << std::endl;
	// debug
	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else {  //set msg to vec
		std::vector<std::string> Buff = configBuff();

// std::cout << "BUFF SIZE ****** " << Buff.size() << std::endl;
		if (PasswordConnect(Buff)== true && users.back()->getJoinServer() == false) {
			addNewUsr((this)->users, Buff);
			std::string sendMsg = users.back()->getPrefix();
			if (users.back()->getNickname() == "")
				return;
			sendMsg += RPL_WELCOME(users.back()->getNickname(), users.back()->getUsername(), users.back()->getHostname());
			sendMsg += delimiter;
			std::cout << "SEND MSG: " << sendMsg << std::endl;
			this->sendReply(sendMsg, *users.back());
			users.back()->setJoinServer(true);
		}
		else {
			if (users.back()->getJoinServer() == true) {
				Invoker _Invoker;
				for (unsigned int i = 0; i < users.size(); i++) {
					if (users[i]->getUserFd() == fd )
					{
						std::string sendMsg =  _Invoker.parser(Buff, users[i], *this);
						std::cout << "\n  ### server :\n" << sendMsg << std::endl;
				
					}
				}
			}
		}
	}
}

}
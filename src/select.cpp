#include "select.hpp"

namespace irc {

// public: class init
Select::Select():serverSocket(), users(), clientfds(), mainSet(), rSet(),wSet() {}
Select::Select(Select const& src) { *this = src; }
Select::~Select() {
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	for(; it != ite; it++)
		delete(*it);
	this->users.clear();
}

Select& Select::operator=(Select const& rhs) {
	if (this == &rhs) return *this;
	this->serverSocket = rhs.serverSocket;
	this->users = rhs.users;
	this->clientfds = rhs.clientfds;
	this->mainSet = rhs.mainSet;
	this->rSet = rhs.mainSet;
	this->wSet = rhs.wSet;
	return *this;
}

// public: serveur creat 
void    Select::serverStart(const short& port, const std::string&  password) {
	this->serverSocket.createServer(port, password);

	FD_ZERO(&this->mainSet); 
	FD_SET(this->serverSocket.getServerFd(), &this->mainSet);//SET servfd to mainset

	for(;;) {
		this->rSet = this->mainSet;
		int event = select(this->max_fd() + 1, &this->rSet, NULL, NULL, NULL);
		if (event < 0) {
			//return;
			continue ;
		}
		for (int fd = 0; fd <= this->max_fd(); fd++) {
			if (FD_ISSET(fd, &this->rSet)) {    // which fd event
				if (fd == this->serverSocket.getServerFd()) { //connect:new client connect 
					this->clientConn();
					break ;
				}
				else {                     //recv
					this->handleReq(fd, 1);
					continue;
				}
			}
		}
	}
}
	


// private: get max fd
int    Select::max_fd() {
	int max = this->serverSocket.getServerFd();
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

	clientConnFd = accept(this->serverSocket.getServerFd(), (struct sockaddr *)&clientAddr, &len);
	if (clientConnFd == SYSCALL_ERR)
		exitFailure("accept failed");

	User *newuser = new User(clientConnFd); 
	this->users.push_back(newuser);// add new user
	this->clientfds.push_back(clientConnFd); //add new fd
	FD_SET(clientConnFd, &this->mainSet);  //add new clientfd to mainset
}

//delete one clientfd
void    Select::clientDisconn(const int clientFd) {
	close(clientFd);
	FD_CLR(clientFd, &this->mainSet);   //delete fd of mainset

	std::vector<int>::iterator it = this->clientfds.begin();
	for (; it != this->clientfds.end(); it++) {
		if (*it == clientFd)
			break ;
	}
	this->clientfds.erase(it);
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
			if (password == this->serverSocket.getPassword()){
				return true;
			}
		}
	}
	return false;
}

std::string		parser(std::vector<std::string> Buff, std::string str) {

	for (std::vector<std::string>::iterator it = Buff.begin(); it != Buff.end(); it++) {
		if ((*it).find(str) != std::string::npos) {
			// size_t pos = (*it).find(str);
			std::string ret = (*it).substr(str.length() + 1);
			return (ret);
		}
	}
	return (NULL);
}

void    Select::handleReq(const int fd, int code) {
	int	ret = -1;

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);   //rece message form clientfd
	std::cout << fd << std::endl;
	std::cout << this->buff << std::endl;

///// verif new nick 
////// set new id

//////
	std::string nn = "no"; 
	// debug
	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else {  //set msg to vec
		std::vector<std::string> Buff = configBuff();
		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
			if ((*(*it)).getNickename() == parser(Buff, "NICK")) {
				std::string newStr = parser(Buff, "NICK") + "_";
				(*(*it)).setNickname(newStr);
				std::cout << newStr << std::endl;
				it = users.begin();
				nn = newStr;
			}
		}
		if (PasswordConnect(Buff)== true && code == 1)
		{
			std::string	sendMsg = RPL_WELCOME(nn);
			 ret = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
			if (ret == SYSCALL_ERR) {
				std::cout << "[Send response failed]" << std::endl;
				this->clientDisconn(fd);
				return;
			}
		}
		else {
			//reply();
			// another cmd ;
		}
	}
}



}
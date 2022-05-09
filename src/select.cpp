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

	for (unsigned int i = 0; i < Buff.size(); i++) {
		if (Buff[i].find(str) != std::string::npos) {
			std::cout << "************* find *****************\n";
			// size_t pos = (*it).find(str);
			std::string ret = Buff[i].substr(Buff[i].find(" ") + 1, Buff[i].length());
			return (ret);
		}
	}
	return ("jules");
}

void		addNewUsr(std::vector<User *> users, std::vector<std::string> Buff) {
	std::string		nick = parser(Buff, "NICK");
	std::string		username;
	int				id;
	std::cout << "********" << nick << "***********\n";
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		for (std::vector<User *>::iterator it2 = it + 1; it2 != users.end(); it2++) {
			if ((*it)->getNickname() == (*it2)->getNickname()) {
				(*it)->setNickname((*(*it)).getNickname()+'_');
				it = users.begin();
				std::cout << "*********" << (*it)->getNickname() << "*****************\n";
			}
		}
	}
	(void)username;
	(void)id;
	
}

void    Select::handleReq(const int fd, int code) {
	int	ret = -1;

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);   //rece message form clientfd
	std::cout << fd << std::endl;
	std::cout << this->buff << std::endl;

	// debug
	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else {  //set msg to vec
		std::vector<std::string> Buff = configBuff();
		/*cap
			pass
			NIcK
			*/
		std::string nick; 
		std::vector<std::string>::iterator it = Buff.begin();
		for(; it != Buff.end(); it++) {
			if ((*it).find("NICK") != std::string::npos) 
			{
				nick = (*it).substr(5);
				for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
					if ((*it)->getNickname() == nick) {
						nick = nick+'_';
						it = users.begin();
					}
				}
				this->users.back()->setNickname(nick);
			}
		}
		// this->users[this->users.size() -1 ]->setNickname(nick);
		// 	std::cout << Buff[0] << "|----\n";
			// if (Buff[0] == static_cast<std::string>("NICK dada"))
			// 	std::string nick = parser(Buff[0], );
		if (PasswordConnect(Buff)== true && code == 1)
		{
			std::string	sendMsg = RPL_WELCOME(nick);
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
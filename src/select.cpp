#include "select.hpp"

_BEGIN_NS_IRC

// public: class init
Select::Select():
	users(),
	serverSocket(),
	mainSet(),
	rSet() {}
Select::Select(Select const& src) { *this = src; }
Select::~Select() {
	this->users.~map();
}

Select& Select::operator=(Select const& rhs) {
	if (this == &rhs) return *this;

	this->serverSocket = rhs.serverSocket;
	this->users = rhs.users;
	this->mainSet = rhs.mainSet;
	this->rSet = rhs.mainSet;
	return *this;
}

// public: serveur create
void    Select::serverStart(const short& port, const std::string&  password) {
	this->serverSocket.createServer(port, password);

	FD_ZERO(&this->mainSet); 
	FD_SET(this->serverSocket.getServerFd(), &this->mainSet);

	for(;;) {
		this->rSet = this->mainSet;
		int event = select(this->max_fd() + 1, &this->rSet, NULL, NULL, NULL);
		if (event < 0) {
			continue ;
		}
		for (int fd = 0; fd <= this->max_fd(); fd++) {
			if (FD_ISSET(fd, &this->rSet)) {
				if (fd == this->serverSocket.getServerFd()) {
					// cli connect to serv
					this->clientConn();
					break ;
				}
				else {
					// handle request
					this->handleReq(fd);
					continue;
				}
			}
		}
	}
}
	


// private: get max fd
int    Select::max_fd() {
	int max = this->serverSocket.getServerFd();
	if (this->users.empty() == true)
		return max;
	else
		max = this->users.rbegin()->first;

	return max;
}


void    Select::clientConn() {
	int					clientConnFd = -1;
	struct sockaddr_in	clientAddr;
	socklen_t			len = sizeof(clientAddr);

	clientConnFd = accept(this->serverSocket.getServerFd(), (struct sockaddr *)&clientAddr, &len);
	if (clientConnFd == SYSCALL_ERR)
		exitFailure("accept failed");

	User newUser(clientConnFd);
	newUser.setHostname(std::string(inet_ntoa(clientAddr.sin_addr)));
	newUser.setUserFd(clientConnFd);
	newUser.setJoinServer(false);

	this->users[clientConnFd] = newUser;

	FD_SET(clientConnFd, &this->mainSet);
}

// delete one clientfd
void    Select::clientDisconn(const int clientFd) {
	close(clientFd);
	FD_CLR(clientFd, &this->mainSet);

	this->users.erase(clientFd);
}

std::vector<std::string> Select::configBuff() {
	std::vector<std::string>	vecBuff;
	std::string 				buf = this->buff;

	vecBuff = ft_split(buf, "\r\n");
	return vecBuff;
}

bool	Select::PasswordConnect(std::vector<std::string> buff){
	size_t								pos = 0;
	std::vector<std::string>::iterator	it = buff.begin();

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

void	Select::handleReq(const int fd) {
	int	ret = -1;

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);
	std::cout << "\n ### client : \n" << this->buff << std::endl;

	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else {
		std::vector<std::string> Buff = configBuff();

		if (PasswordConnect(Buff) == true) {
			std::string	sendMsg = RPL_WELCOME(this->users[fd].getNickname(), this->users[fd].getUsername(),this->users[fd].getHostname());
		
			std::cout << "debug send msg: " << sendMsg <<std::endl;

			ret = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
			if (ret == SYSCALL_ERR) {
				std::cout << "[Send response failed]" << std::endl;
				this->clientDisconn(fd);
				return;
			}
			this->users[fd].setJoinServer(true);
		}

		if (this->users[fd].getJoinServer() == true) {
			// do command
		}
	}
}


_END_NS_IRC
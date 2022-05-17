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
	newuser->setHostname(std::string(inet_ntoa(clientAddr.sin_addr)));
	newuser->setJoinServer(false);
	// std::cout<<"hostname: "<<newuser->getHostname()<<std::endl; 
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
			if (password == this->_serverSocket.getPassword()){
				return true;
			}
		}
	}
	return false;
}
void                   Select::addChannel(std::string channelName) {

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
					nick = nick+'_';
					it = users.begin();
				}
			}
			users.back()->setNickname(nick);
		}
	}

	(users.back())->setId(users);
	(users.back())->setName(Buff);
}

void Select::sendMsg(std::string msg, User *user){
	int ret = -1;

	ret = send(user->getUserFd(), msg.c_str(), msg.length(), 0);
	if (ret == SYSCALL_ERR) {
		std::cout << "[Send response failed]" << std::endl;
		this->clientDisconn(user->getUserFd());
		return;
	}
}

void    Select::handleReq(const int fd) {
	int	ret = -1;

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);   //rece message form clientfd
	// std::cout << fd << std::endl;
	std::cout << "\n ### client : \n" << this->buff << std::endl;
	// debug
	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else {  //set msg to vec
		std::vector<std::string> Buff = configBuff();

		if (PasswordConnect(Buff)== true ) {
			addNewUsr((this)->users, Buff);
			
			std::string	sendMsg = RPL_WELCOME(users.back()->getNickname(), users.back()->getHostname(),
			users.back()->getUsername());
			std::cout << sendMsg << std::endl;
			ret = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
			if (ret == SYSCALL_ERR) {
				std::cout << "[Send response failed]" << std::endl;
				this->clientDisconn(fd);
				return;
			}
		}
		else {
			Invoker _Invoker;
			for (unsigned int i = 0; i < users.size(); i++) {
				if (users[i]->getUserFd() == fd )
				{
					// std::string sM = ":irc.42team 221 " + users.back()->getNickname(); 
					// send(fd, sM.c_str(), sM.length(), 0);
					//Select *tmp = this;
					std::string	sendMsg = _Invoker.parser(Buff, users[i], *this);
					std::cout << "\n  ### server :\n" << sendMsg << std::endl;
					// ret = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
					if (ret == SYSCALL_ERR) {
						std::cout << "[Send response failed]" << std::endl;
						this->clientDisconn(fd);
						return;
					}
				}
			}
		}
		//}
		}
			// std::cout << "----->" << std::find(this->users.begin(), this->users.end(), User(fd, false)) << std::endl;
			// parser(Buff, (*(this)->users.find(fd)))
}

}
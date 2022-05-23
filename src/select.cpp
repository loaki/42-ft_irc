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
				if (BOTCREATE && !botIsCon) {
					botConn(password);
					break;
				}
				else if (fd == this->_serverSocket.getServerFd()) { //connect:new client connect 
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

void Select::botConn(std::string pass) {

	int                 clientConnFd = -1;
	struct sockaddr_in	clientAddr;
	socklen_t			len = sizeof(clientAddr);

	clientConnFd = accept(this->_serverSocket.getServerFd(), (struct sockaddr *)&clientAddr, &len);
	if (clientConnFd == SYSCALL_ERR)
	{	exitFailure("accept failed");}
	
	Bot * newuser = new Bot(clientConnFd, pass);
	newuser->setHostname(std::string(inet_ntoa(clientAddr.sin_addr)));
	newuser->setJoinServer(false);

	this->users.push_back(newuser);// add new user
	this->clientfds.push_back(clientConnFd); //add new fd
	FD_SET(clientConnFd, &this->mainSet);  //add new clientfd to mainset


	newuser->addBot(this);
	
	botFD = clientConnFd;
	botIsCon = true;
	hasJoined = false;
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

	if (fcntl(clientConnFd, F_SETFL, O_NONBLOCK) == SYSCALL_ERR) {
        close(clientConnFd);
        exitFailure("fcntl failed");
    }
	
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

bool	Select::checkNameInBuff(std::vector<std::string> buff, std::string name){
	std::vector<std::string>::iterator it = buff.begin();
	std::vector<std::string>::iterator ite = buff.end();
	for(; it != ite; it++) {
		if ((*it).find(name) != std::string::npos) 
				return true;
	}
	return false;
}

void		Select::addNewUsr(int fd, std::vector<std::string> Buff) {
	bool to_set = true;
	std::string nick;
	User	*user = NULL;
	std::vector<std::string>::iterator it = Buff.begin();
	for (std::vector<User *>::iterator uit = users.begin(); uit != users.end(); uit++) {
		if ((*uit)->getUserFd() == fd) {
			user = *uit;
			break ;
		}
	}
	for(; it != Buff.end(); it++) {
		if ((*it).find("NICK") != std::string::npos) 
		{
			nick = (*it).substr(5);
			for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
				if ((*it)->getNickname() == nick && fd != botFD) {
					std::string msg = ":";
					msg += ERR_NICKNAMEINUSE(nick);
					std::cout << "normal MESSAGE USER FALSE: " << msg << std::endl;
					send(user->getUserFd(), msg.c_str(), msg.length(), 0) ;
					to_set = false;
				}
			}
			if (to_set)
				user->setNickname(nick);
		}
	}
	user->setName(Buff);
	if (user->getNickname() != "" && user->getUsername() != "" ) {
		user->setChunk(false);
		std::string sendMsg = user->getPrefix();
		sendMsg += RPL_WELCOME(user->getNickname(), user->getUsername(), user->getHostname());
		sendMsg += delimiter;
		std::cout << sendMsg << std::endl;
		this->sendReply(sendMsg, *user);
		user->setJoinServer(true);
	}
}

void		Select::addNewUsrChunk(int fd, std::vector<std::string> Buff, bool withComplete) {
	bool	to_set = true;
	std::string nick; 
	std::vector<std::string>::iterator it = Buff.begin();
	User	*user = NULL;
	for (std::vector<User *>::iterator uit = users.begin(); uit != users.end(); uit++) {
		if ((*uit)->getUserFd() == fd) {
			user = *uit;
			break ;
		}
	}
	if (user != NULL) {
		for(; it != Buff.end(); it++) {
			if ((*it).find("NICK") != std::string::npos) 
			{
				nick = (*it).substr(5);
				if (withComplete == false) {
					for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
						if ((*it)->getNickname() == nick) {
							std::string msg = ":";
							msg += ERR_NICKNAMEINUSE(nick);
							std::cout << "in chunk MESSAGE USER FALSE: " << msg << std::endl;
							send(fd, msg.c_str(), msg.length(), 0) ;
							to_set = false;
						}
					}
					if (to_set)
						user->setNickname(nick);
				}
			}
			if (it->find("PASS") != std::string::npos)
				user->setPass(it->substr(5));
			if (it->find("USER") != std::string::npos)
				user->setName(Buff);
		}
		if (user->getNickname() != "" && user->getPass() != "" && user->getUsername() != "" && user->getPass() == this->_serverSocket.getPassword()) {
			user->setChunk(false);
			std::string sendMsg = user->getPrefix();
			sendMsg += RPL_WELCOME(user->getNickname(), user->getUsername(), user->getHostname());
			sendMsg += delimiter;
			std::cout << sendMsg << std::endl;
			this->sendReply(sendMsg, *user);
			user->setJoinServer(true);
			user->setChunk(false);
		}
	}
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

bool Select::userInVec(int fd) {
	if (this->users.size() == 0)
		return false;
	std::vector<User *>::iterator it = users.begin();
	for(; it != users.end(); it++) {
		if ((*it)->getUserFd() == fd)
			return true;
	}
	return false;
}

bool	Select::competeConnect(std::vector<std::string> buff) {
	if (this->checkNameInBuff(buff, "CAP")
		&& this->checkNameInBuff(buff, "NICK")
		&& this->checkNameInBuff(buff, "USER")
		&& this->checkNameInBuff(buff, "PASS"))
		return true;
	return false;
}

bool	Select::chunkConnect(std::vector<std::string> buff) {
	if (this->checkNameInBuff(buff, "CAP")
		|| this->checkNameInBuff(buff, "NICK")
		|| this->checkNameInBuff(buff, "USER")
		|| this->checkNameInBuff(buff, "PASS"))
		return true;
	return false;
}

bool	Select::needChunk(int fd) {
	if (this->users.size() == 0)
		return false;
	std::vector<User *>::iterator it = users.begin();
	for(; it != users.end(); it++) {
		if ((*it)->getUserFd() == fd && (*it)->getChunk() == true)
			return true;
	}
	return false;
}

bool	Select::ifJoinServer(int fd) {
	std::vector<User *>::iterator it = users.begin();
	for(; it != users.end(); it++) {
		std::cout << "check join fd: " << (*it)->getUserFd() << "compare with: " << fd << std::endl;
		std::cout << "check join cd: " << (*it)->getJoinServer() << std::endl;
		if ((*it)->getUserFd() == fd && (*it)->getJoinServer() == true)
			return true;
	}
	std::cout << "Can't execute cmd\n";
	return false;
}

void    Select::handleReq(const int fd) {
	int	ret = -1;

	bzero(this->buff, sizeof(this->buff));
	ret = recv(fd, this->buff, MAX_BUFF, 0);   //recv message form clientfd

	std::cout << "\n ### client : \n" << this->buff << std::endl;
	// debug
	if (ret <= 0) { 
		this->clientDisconn(fd);
		return ;
	}
	else if (fd == botFD && !hasJoined) {
		// std::vector<std::string> C(1);
		std::string msg = "JOIN #botChan";
		for (unsigned int i = 0; i < users.size(); i++) {
			if (users[i]->getUserFd() == fd )
			{
				// std::string sendMsg =  _Invoker.parser(Buff, users[i], *this);
				int ret = -1;
				ret = send(fd, msg.c_str(), msg.length(), 0);
				std::cout << "\n  ### BOT ***** server :\n" << ret << std::endl;
			}
		}
		hasJoined = true;
		bzero(this->buff, sizeof(this->buff));
		return;
	} 
	else {  //set msg to vec
		bool	to_execute = true;
		bool	with_complete = false;
		std::vector<std::string> Buff = configBuff();
		std::cout << "BUFF SIZE: " << Buff.size() << std::endl;
		std::cout << "cmd: " << Buff[0] << "with fd: " << fd << std::endl;
		Invoker _Invoker; 
		if (fd == botFD && !hasJoined) {
			// std::vector<std::string> C(1);
			std::string msg = "JOIN #botChan";
			for (unsigned int i = 0; i < users.size(); i++) {
				if (users[i]->getUserFd() == fd )
				{
					// std::string sendMsg =  _Invoker.parser(Buff, users[i], *this);
					int ret = -1;
					ret = send(fd, msg.c_str(), msg.length(), 0);
					std::cout << "\n  ### BOT ***** server :\n" << ret << std::endl;
				}
			}
			hasJoined = true;
		} 
		
		if (this->competeConnect(Buff) && PasswordConnect(Buff)== true && ifJoinServer(fd) == false) {
			addNewUsr(fd, Buff);
			std::cout<<"****1"<<std::endl;
			to_execute = false;
			with_complete = true;
		}

		if (this->chunkConnect(Buff) && this->needChunk(fd) == true && ifJoinServer(fd) == false) {
			// msg already name exist call 2 time ... need debug this
			std::cout<<"****2"<<std::endl;
			this->addNewUsrChunk(fd, Buff, with_complete);
			to_execute = false;
		}

		if (to_execute == true && ifJoinServer(fd) == true) {
			std::cout<<"****3"<<std::endl;
			// Invoker _Invoker;
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
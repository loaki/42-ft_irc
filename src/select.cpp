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

std::vector<User *> Select::getUsers(){return this->users;}
 std::vector<Channel *> Select::getAllChannel() {return this->_channels;}
 
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
			if (password == this->serverSocket.getPassword()){
				return true;
			}
		}
	}
	return false;
}

// std::string		parser(std::vector<std::string> Buff, std::string str) {

// 	for (unsigned int i = 0; i < Buff.size(); i++) {
// 		if (Buff[i].find(str) != std::string::npos) {
// 			std::cout << "************* find *****************\n";
// 			// size_t pos = (*it).find(str);
// 			std::string ret = Buff[i].substr(Buff[i].find(" ") + 1, Buff[i].length());
// 			return (ret);
// 		}
// 	}
// 	return ("jules");
// }

std::string		craftId() {
	std::string s;

	static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
	srand( time( 0 ) );
	for (int i = 0; i < 10; ++i) {
		s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return (s);
}

void		setId(std::vector<User *> users, User * user) {

	user->setUserId(craftId());
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
		if ((user->getUserId() == (*(*it)).getUserId()) && user != (*it)) {
			user->setUserId(craftId());
			it = users.begin();
		}
	}
}

void		setName(User *user, std::vector<std::string> Buff) {

	for (std::vector<std::string>::iterator it = Buff.begin(); it != Buff.end(); it++) {
		if ((*it).find("USER") != std::string::npos) 
		{
			std::string temp = (*it).substr(5);
			int end = temp.find(" ");
			user->setUsername(temp.substr(0, end));
		}
	}
}

void		addNewUsr(std::vector<User *> users, std::vector<std::string> Buff) {

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
	
	setId(users, users.back());
	setName(users.back(), Buff);
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

		if (PasswordConnect(Buff)== true) {
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
			
			//add this->users[fd]->setJoinServer(true);
		}
		/*after lucien changer vector to std::map<int, user> user;*/
		//if (this->users[fd]->setJoinServer(true) {
			/*already connecter we can parser commands
				Msg += ":";
				Msg += nickname;
				Msg += "!";
				Msg += username;
				Msg += "@";
				Msg += hostname;
			*/
		else {
			Invoker _Invoker;
			for (unsigned int i = 0; i < users.size(); i++) {
				if (users[i]->getUserFd() == fd)
				{
					// std::string sM = ":irc.42team 221 " + users.back()->getNickname(); 
					// send(fd, sM.c_str(), sM.length(), 0);
					//Select *tmp = this;
					std::string	sendMsg = _Invoker.parser(Buff, users[i], *this);
					std::cout << "\n  ### server :\n" << sendMsg << std::endl;
					ret = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
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
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
            return;
            //continue ;
        }
        for (int fd = 0; fd <= this->max_fd(); fd++) {
            if (FD_ISSET(fd, &this->rSet)) {               //which fd event
                if (fd == this->serverSocket.getServerFd()) { //new client connect 
                    this->clientConn(); 
                    break ;
                }
                else {
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
    std::cout <<"add new user" << newuser->getUserFd() << std::endl;

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

bool Select::PasswordConnect(){

    size_t pos = 0;
    size_t pos2 = 0;
    std::string tmp = this->buff;
    if (tmp.find("PASS") != std::string::npos)
        pos = tmp.find("PASS");
    std::string pass = tmp.substr(pos);

    if (pass.find("\r\n") != std::string::npos)
        pos2 = pass.find("\r\n");
    std::string tmp2 = pass.substr(0, pos2);
    std::string password = tmp2.substr(5);

    if (password == this->serverSocket.getPassword())
        return true;
    return false;
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
    else {
        if (PasswordConnect()== true && code == 1)
        {
            std::string bufTmp = ":xueming 001 wang :Welcome to the Internet Relay Network!xuemingwang@localhost\r\n"; //+  nick + "!" + username + "@" + host
            ret = send(fd, bufTmp.c_str(), bufTmp.length(), 0);
            if (ret == SYSCALL_ERR) {
            // debug
                std::cout << "[Send response failed]" << std::endl;
                this->clientDisconn(fd);
                return;
            }
        }
    }
}



}
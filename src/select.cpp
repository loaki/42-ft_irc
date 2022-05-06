#include "select.hpp"

namespace irc {
// ns begin

/*
 * public
 */

// public: class init
Select::Select() {}
Select::Select(Select const& src) { *this = src; }
Select::~Select() {}
Select& Select::operator=(Select const& rhs) {
    if (this == &rhs) return *this;

    this->serverSock = rhs.serverSock;
    this->clientFd = rhs.clientFd;
    this->mainSet = rhs.mainSet;
    this->rSet = rhs.mainSet;
    this->wSet = rhs.wSet;
    return *this;
}

// public: method
void    Select::serverStart(const short& port, const std::string&  password) {
    this->serverSock.createServer(port, password);

    FD_ZERO(&this->mainSet);
    FD_SET(this->serverSock.getServerFd(), &this->mainSet);//SET servfd to mainset

    for(;;) {
        this->rSet = this->mainSet;

        int event = select(this->max_fd() + 1, &this->rSet, NULL, NULL, NULL);
        if (event < 0) {
            return;
           // continue ;
        }
        for (int fd = 0; fd <= this->max_fd(); fd++) {
            if (FD_ISSET(fd, &this->rSet)) {               //which fd event
                if (fd == this->serverSock.getServerFd()) { //new client connect 
                    this->clientConn(); 
                    break ;
                }
                else {
                    this->handleReq(fd, 1);
                }
                    // { 
                    //     continue;
                    // }
                }
            }
        }
}
    


// private: method
int    Select::max_fd() {
    int max = this->serverSock.getServerFd();

    if (this->clientFd.empty())
        return max;
    
    for (std::vector<int>::iterator it = this->clientFd.begin(); it != this->clientFd.end(); it++) {
        if (*it > max)
            max = *it;
    }
    return max;
}

void    Select::clientConn() { //get client fd  
    int                 clientConnFd = -1;
    struct sockaddr_in	cli;
	socklen_t			len = sizeof(cli);

    clientConnFd = accept(this->serverSock.getServerFd(), (struct sockaddr *)&cli, &len);
    if (clientConnFd == SYSCALL_ERR)
        exitFailure("accept failed");

    this->clientFd.push_back(clientConnFd);// push_back clientFd 
    FD_SET(clientConnFd, &this->mainSet);  //add new clientfd to mainset
}

void    Select::clientDisconn(const int clientFd) {
    close(clientFd);
    FD_CLR(clientFd, &this->mainSet);   //delete fd

    std::vector<int>::iterator it = this->clientFd.begin();
    for (; it != this->clientFd.end(); it++) {
        if (*it == clientFd)
            break ;
    }
    this->clientFd.erase(it);
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

    if (password == this->serverSock.getPassword())
        return true;
    return false;
}
void    Select::handleReq(const int fd, int code) {
    int	ret = -1;

    bzero(this->buff, sizeof(this->buff));
    ret = recv(fd, this->buff, MAX_BUFF, 0);   //rece message form clientfd
    std::cout   << this->buff << std::endl;
    // debug
    if (ret <= 0) { 
        this->clientDisconn(fd);
        return ;
    }
    else {
        if (PasswordConnect()== true && code == 1)
        {
            std::string bufTmp = ":xueming 001 wang :Welcome to the Internet Relay Networkxuemingwang!xuemingwang@localhost\r\n"; //+  nick + "!" + username + "@" + host
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
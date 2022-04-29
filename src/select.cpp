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
void    Select::serverStart() {
    this->serverSock.createServer(SERVER_PORT);

    FD_ZERO(&this->mainSet);
    FD_SET(this->serverSock.getServerFd(), &this->mainSet);//SET servfd to mainset

    for(;;) {
        this->rSet = this->mainSet;

        int event = select(this->max_fd() + 1, &this->rSet, NULL, NULL, NULL);
        if (event < 0) {
            continue ;
        }

        for (int fd = 0; fd <= this->max_fd(); fd++) {
            if (FD_ISSET(fd, &this->rSet)) {                //which fd event
                if (fd == this->serverSock.getServerFd()) { //new client nconnect 
                    this->clientConn(); 
                    break ;
                }
                else {
                    if (this->handleReq(fd) == false)
                        continue;
                }
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
        exitFailure("accept function failed");

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

bool    Select::handleReq(const int fd) {
    int	ret = -1;

    bzero(this->buff, sizeof(this->buff));
    ret = recv(fd, this->buff, MAX_BUFF, 0);   //rece message form clientfd 
    // debug
    std::cout << "Message from fd:" << fd << "\n" << this->buff << std::endl;
    //
    if (ret <= 0) { 
        this->clientDisconn(fd);
        return false;
    }
    else {
        std::string bufTmp = std::string(this->buff);
        sentToAll(fd, bufTmp);
    }
    return true;
}

void Select::sentToAll(const int fd, std::string str) {
    int ret = -1;
    for(unsigned int i = 0; i < this->clientFd.size(); i++) {
        if (this->clientFd.at(i) != fd ) {
            ret = send(this->clientFd.at(i), str.c_str(), str.length(), 0);
            if (ret == SYSCALL_ERR) {
            // debug
            std::cout << "[Send response failed]" << std::endl;
            this->clientDisconn(i);
            }
        }
    }
}

}
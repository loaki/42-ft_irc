#include "select.hpp"

namespace webserv {
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
                    printf("in handle\n");
                    if (this->handleReq(fd) == false)
                        break ;
                    else
                        this->handleRes(fd);
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
    ret = recv(fd, this->buff, MAX_BUFF, 0);
    // debug
    std::cout << "===========\nrequest:\n" << this->buff << "\n=============\n" << std::endl;
    //
    if (ret <= 0) {
        this->clientDisconn(fd);
        return false;
    }
    else {
        std::string bufTmp = std::string(this->buff);
        this->req.parse_Request(bufTmp);

        printf("method: [%s]\n", this->req.getReq().method.c_str());
        printf("url: [%s]\n", this->req.getReq().url.c_str());
        printf("host: [%s]\n", this->req.getReq().version.c_str());
        printf("body: [%s]\n", this->req.getReq().body.c_str());

        std::map<std::string, std::string> tmp = this->req.getReq().header;
        std::map<std::string, std::string>::iterator it = tmp.begin();
        std::map<std::string, std::string>::iterator ite = tmp.end();
        for (; it != ite; it++) {
            std::cout << it->first << ": " << it->second << std::endl;
        }

        std::cout << std::endl;
    }
    return true;
}

void    Select::handleRes(const int fd) {
    int ret = -1;
    
    //test response
    std::string respTest = "\   
HTTP/1.1 200 OK\r\n\
Server: Microsoft-IIS/5.1\r\n\
X-Powered-By: ASP.NET\r\n\
Date: Fri, 03 Mar 2006 06:34:03 GMT\r\n\
Content-Type: text/html\r\n\
Accept-Ranges: bytes\r\n\
Last-Modified: Fri, 03 Mar 2006 06:33:18 GMT\r\n\
ETag: \"5ca4f75b8c3ec61:9ee\"\r\n\
Content-Length: 37\r\n\
\r\n\
<html><body>hello world</body></html>";

    ret = send(fd, respTest.c_str(), respTest.length(), 0);
    if (ret == SYSCALL_ERR) {
        // debug
        std::cout << "[Send response failed]" << std::endl;
        
        this->clientDisconn(fd);
    }
    this->clientDisconn(fd);
}

// ns end
}
#include "socket.hpp"

namespace webserv {
// ns begin

/*
* public
*/

// public: class init
Socket::Socket():
    _serverFd(-1),
    _port(SERVER_PORT) {
    std::memset(&this->_serverAddr, 0, sizeof(struct sockaddr_in));
}
Socket::Socket(Socket const & src) { *this = src; }
Socket::~Socket() {}

Socket & Socket::operator=(const Socket & rhs) {
    if (this == &rhs) return *this;

    this->_serverFd = rhs._serverFd;
    this->_port = rhs._port;
    this->_serverAddr = rhs._serverAddr;
    return *this;
}

// public: getter & setter
const int & Socket::getServerFd() const { return this->_serverFd; }

// public: method
void Socket::createServer(const short & port) {
    this->serverInit(port);
    this->serverBind();
    this->serverListen();
}

/*
* private
*/

// private: method
void Socket::serverInit(const short & port) {
    this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_serverFd == SYSCALL_ERR)
        exitFailure("socket function failed");
    
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_port = htons(port);
    this->_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0, all ip can acces, but need change later with a precise ip address (ex: inet_addr(localhost?))

    int	optval = 1;
	if (SYSCALL_ERR == setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) { // can rebind port
		close(this->_serverFd);
		exitFailure("setsockopt()");
	}
}

void Socket::serverBind() {
    if (bind(this->_serverFd, (struct sockaddr *)&this->_serverAddr, sizeof(struct sockaddr)) == SYSCALL_ERR)
        exitFailure("bind function failed");
}

void Socket::serverListen() {
    if (listen(this->_serverFd, SOMAXCONN) == SYSCALL_ERR)
        exitFailure("bind function failed");
}


// ns end
}
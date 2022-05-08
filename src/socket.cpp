#include "socket.hpp"

namespace irc {
// ns begin

// public: class init
Socket::Socket():
    _serverFd(-1),
    _port(),
    _password() {
    memset(&this->_serverAddr, 0, sizeof(struct sockaddr_in));
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
const std::string & Socket::getPassword() const {return this->_password;}
void Socket::setPassword(std::string password) { this->_password = password;}

// public: method
void Socket::createServer(const short & port, const std::string&  password) {
    this->_password = password;
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
        exitFailure("socket failed");
    
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_port = htons(port); // (host to net)
    this->_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0, all ip can acces, (host to net)

    int	optval = 1;
    // int  setsockopt(int  s, int level, int optname, void* optval, socklen_t* optlen);
	if (SYSCALL_ERR == setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) { // can rebind port
		close(this->_serverFd);
		exitFailure("setsockopt failed");
	}
    // get／set mutex 设置给arg描述符状态标志
    // O_NONBLOCK   非阻塞I/O，如果read(2)调用没有可读取的数据，或者如果write(2)操作将阻塞，则read或write调用将返回-1和EAGAIN错误
    if (fcntl(this->_serverFd, F_SETFL, O_NONBLOCK) == SYSCALL_ERR)
    {
        close(this->_serverFd);
        exitFailure("fcntl failed");
    }
}

void Socket::serverBind() {
    if (bind(this->_serverFd, (struct sockaddr *)&this->_serverAddr, sizeof(struct sockaddr)) == SYSCALL_ERR)
        exitFailure("bind failed");
}

void Socket::serverListen() {
    if (listen(this->_serverFd, SOMAXCONN) == SYSCALL_ERR)
        exitFailure("listen failed");
}


// ns end
}
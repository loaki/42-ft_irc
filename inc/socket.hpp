#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "defs.hpp"

namespace webserv {
// ns begin

/*
 * Socket class
 */
class Socket {
    public:
    // public: class init
        Socket();
        Socket(Socket const& src);
        ~Socket();
        Socket& operator=(Socket const& rhs);

    // public: getter & setter
        const int & getServerFd() const;

    // public: method
        void    createServer(const short & port);

    private:
    // private: method
        void    serverInit(const short & port);
        void    serverBind();
        void    serverListen();

    // private: attributs
        int                 _serverFd;
        short               _port;
        struct sockaddr_in  _serverAddr;
};

// ns end
}

#endif
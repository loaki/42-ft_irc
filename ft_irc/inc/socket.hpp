#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "defs.hpp"
#include "socket.hpp"

namespace irc {
// ns begin


class Socket {
    public:
    // public: class init
        Socket();
        Socket(Socket const& src);
        ~Socket();
        Socket& operator=(Socket const& rhs);

    // public: getter & setter
        int const&          getServerFd() const;
        std::string const&  getPassword() const;
        void                setPassword(std::string password);

    // public: method
        void                createServer(const short & port, const std::string&  password);

    private:
    // private: method
        void                serverInit(const short & port);
        void                serverBind();
        void                serverListen();

    // private: attributs
        int                 _serverFd;
        short               _port;
        std::string         _password;
        struct sockaddr_in  _serverAddr;
    
};

// ns end
}

#endif
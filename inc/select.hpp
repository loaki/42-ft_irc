#ifndef SELECT_HPP
# define SELECT_HPP

#include "defs.hpp"
#include "socket.hpp"

namespace irc {
// ns begin

class Select {
    public:
    // public: class init
        Select();
        Select(Select const& src);
        ~Select();
        Select& operator=(Select const& rhs);

    // public: method
        void    serverStart(const short& port, const std::string&  password);

    private:
    // private: method
        int     max_fd();
        void    clientConn();
        void    clientDisconn(const int clientFd);
        bool    PasswordConnect();
        void    handleReq(const int fd, int code);
        void    sentToAll(const int fd,  std::string str);

    // private: attributs
        Socket              serverSock;
        std::vector<int>    clientFd;
        fd_set              mainSet;
        fd_set              rSet;
        fd_set              wSet; // currently no use

        char                buff[MAX_BUFF];
        
};

// ns end
}

#endif
#ifndef SELECT_HPP
# define SELECT_HPP

#include "defs.hpp"
#include "socket.hpp"
#include "request.hpp"

namespace webserv {
// ns begin

class Select {
    public:
    // public: class init
        Select();
        Select(Select const& src);
        ~Select();
        Select& operator=(Select const& rhs);

    // public: method
        void    serverStart();

    private:
    // private: method
        int     max_fd();
        void    clientConn();
        void    clientDisconn(const int clientFd);
        bool    handleReq(const int fd);
        void    handleRes(const int fd);

    // private: attributs
        Socket              serverSock;
        std::vector<int>    clientFd;
        fd_set              mainSet;
        fd_set              rSet;
        fd_set              wSet; // currently no use

        char                buff[MAX_BUFF];
        Request             req;
};

// ns end
}

#endif
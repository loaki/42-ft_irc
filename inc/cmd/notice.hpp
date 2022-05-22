#ifndef NOTICE_HPP
# define NOTICE_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"
namespace irc {

class Notice :public Command {
    public:
        Notice();
        virtual ~Notice();

        std::string execute(std::string line, User *user, Select &select);
};

}

#endif
#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"
namespace irc {

class Privmsg :public Command {
    public:
        Privmsg();
        virtual ~Privmsg();

        std::string execute(std::string line, User *user, Select &select);
       	std::string botResponse(std::string msg);

};

}

#endif
#ifndef PING_HPP
# define PING_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

namespace irc {

class Ping: public Command {
    public:
        Ping();
        virtual ~Ping();

        std::string execute(std::string line, User * user, Select *select);

};


}

#endif
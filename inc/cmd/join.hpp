#ifndef JOIN_HPP
# define JOIN_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

namespace irc {

class Join: public Command {
    public:
        Join();
        virtual ~Join();

        //std::string execute(std::string line, User * user, Select &select);

};



}


#endif
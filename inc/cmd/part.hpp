#ifndef PART_HPP
# define PART_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"
namespace irc {

class Part :public Command {
    public:
        Part();
        virtual ~Part();

        std::string execute(std::string line, User *user, Select &select);
};

}

#endif
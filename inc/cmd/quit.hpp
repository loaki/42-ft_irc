#ifndef QUIT_HPP
# define QUIT_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

namespace irc {

class Quit :public Command {
    public:
        Quit();
        virtual ~Quit();

        std::string execute(std::string line, User *user, Select &select);
};

}

#endif
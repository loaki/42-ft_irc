#ifndef INVOKER_HPP
# define INVOKER_HPP

#include "defs.hpp"
#include "command.hpp"
#include "select.hpp"

namespace irc {

class Select;
class Command;

class Invoker {

    public:
        Invoker();
        virtual~Invoker();
        std::string parser(std::vector<std::string> Buff, User * user, Select &select);

    private:
        std::vector<Command*>	_commands;
};
}

#endif
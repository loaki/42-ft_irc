#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "defs.hpp"
#include "ping.hpp"
#include "nick.hpp"
#include "select.hpp"

namespace irc {

        std::string part(std::string line, User * user);

class Command {
    public:
        Command();
        ~Command();
        std::string parser(std::vector<std::string> Buff, User * user);
        typedef std::string (*fct_ptr)(std::string, User *);

    private:
        Ping cmd_ping;
        Nick cmd_nick;
    };
}

#endif
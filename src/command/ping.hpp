#ifndef PING_HPP
# define PING_HPP

#include "defs.hpp"

namespace irc {

class Ping {
    public:
        Ping();
        ~Ping();

        static std::string _ping(std::string line, User * user);
};

}

#endif
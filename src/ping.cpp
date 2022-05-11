#include "ping.hpp"

namespace irc {

Ping::Ping() {}
Ping::~Ping() {}

// void Ping::timeout()

std::string Ping::_ping(std::string line, User * user) {
    (void)user;
    std::vector<std::string> v_cmd = ft_split(line, " ");
    if (v_cmd.size() < 2) {
        std::string msg = ERR_NOORIGIN;
        msg += delimiter;
        return msg;
    }
    return std::string("PONG :" + v_cmd[1]);
}

} 
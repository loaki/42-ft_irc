#include "ping.hpp"

namespace irc {

Ping::Ping() {}
Ping::~Ping() {}

// void Ping::timeout()

std::string Ping::_ping(std::string line, User * user) {
    std::string msg;
    (void)user;
    std::vector<std::string> v_cmd = ft_split(line, " ");
    if (v_cmd.size() < 2) {
        msg = ERR_NOORIGIN;
        msg += delimiter;
        return msg;
    }
    msg = "PONG :" + v_cmd[1] + delimiter;
    return msg;
}

} 
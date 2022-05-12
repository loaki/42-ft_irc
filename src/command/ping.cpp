#include "ping.hpp"
#include "select.hpp"

namespace irc {

Ping::Ping() {
    _name = "PING";
}
Ping::~Ping() {}

// void Ping::timeout()

std::string Ping::execute(std::string line, User * user, Select *select) {
    std::string msg;
    (void)user;
    (void)select;
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
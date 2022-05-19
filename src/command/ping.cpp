#include "ping.hpp"

namespace irc {

Ping::Ping() { _name = "PING";}
Ping::~Ping() {}

std::string	Ping::execute(std::string line, User * user, Select &select) {
    std::string msg;
    
    std::vector<std::string> v_cmd = ft_split(line, " ");
    if (v_cmd.size() < 2) {
        msg = ERR_NOORIGIN();
        msg += delimiter;
        select.sendReply(msg, user);
        return msg;

    }
    msg = user->getPrefix() + " PONG :" + v_cmd[1] + delimiter;
    select.sendReply(msg, user);
    return msg;
}

} 
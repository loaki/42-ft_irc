#include "part.hpp"

_BEGIN_NS_IRC

Part::Part() {}
Part::~Part() {}

// void Ping::timeout()

std::string Part::_part(std::string line, User * user) {
    std::vector<std::string> v_cmd = ft_split(line, " ");
    if (v_cmd.size() < 2) {
        std::string msg = ERR_NOORIGIN;
        msg += DELIM;
        return msg;
    }
    return std::string("PONG :" + v_cmd[1] + DELIM);
}

} 
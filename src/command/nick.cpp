#include "nick.hpp"

#define MAX_SIZE 9

namespace irc {

Nick::Nick() {}
Nick::~Nick() {}


std::string Nick::_nick(std::string line, Select &sel) {
    std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
    std::string nickname = v_cmd[1];
    if (v_cmd.size() != 2 || nickname.leght() == 0) {
        msg = ERR_NONICKNAMEGIVE;
        msg += delimiter;
        return msg;
    }
    std::vector<User *>::iterator it = sel.getUsers().begin();
    for(; it != sel.getUsers().begin(); it++) {
        if ((*it)->getNickname() == nickname) {
            msg = ERR_NICKNAMEINUSE(nickname);
            msg += delimiter;
            return msg;
        }
    }
    


    return msg;
}















}
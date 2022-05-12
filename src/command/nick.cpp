#include "nick.hpp"

//英文字母，數字
namespace irc {

Nick::Nick() {}
Nick::~Nick() {}

//ERR_NICKNAMEINUSE :aleardy use in user
bool Nick::nickinUse(std::string name, Select &select) {
    std::vector<User *>::iterator it = select.getUsers().begin();
    for(; it != select.getUsers().begin(); it++) \
        if ((*it)->getNickname() == name)
            return true;
    return false;
}

//ERR_ERRONEUSNICKNAME: erro nickname
bool Nick::nameError(std::string name){
    if(name.length() > MAX_SIZE)
        return false;
    for(size_t i = 0; i < name.size(); i++){
        if (!isalnum(name[i]))
            return false;
    }
    return true;
}

std::string Nick::_nick(std::string line, User *user, Select &select) {
    std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
    std::string nickname = v_cmd[1];
    //ERR_ERRONEUSNICKNAME: erro nickname
    if (nameError(nickname) == false) {
         msg = ERR_ERRONEUSNICKNAME(nickname);
         msg += delimiter;
         return msg;
    }
    //RR_NONICKNAMEGIVEN: don t nickname given
    if (v_cmd.size() != 2 || nickname.length() == 0) {
        msg = ERR_NONICKNAMEGIVEN;
        msg += delimiter;
        return msg;
    }
    //ERR_NICKNAMEINUSE :aleardy use in user
    if (nickinUse(nickname, select) == true) {
            msg = ERR_NICKNAMEINUSE(nickname);
            msg += delimiter;
            return msg;
    }
    user->setNickname(nickname);
    msg = ":" + user->getNickname() + line;
    return msg;
}

}
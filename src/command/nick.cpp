#include "nick.hpp"

//英文字母，數字
namespace irc {

Nick::Nick() {
    _name = "NICK";
}
Nick::~Nick() {}

//ERR_NICKNAMEINUSE :aleardy use in user
bool	Nick::nickinUse(std::string name, std::vector<User *> users) {
    std::vector<User *>::iterator it = users.begin();
    for(; it != users.end(); it++)
        if ((*it)->getNickname() == name)
            return true;
    return false;
}


//ERR_ERRONEUSNICKNAME: erro nickname
bool	Nick::nameError(std::string name){
    if(name.length() > MAX_SIZE)
        return false;
		
    for(size_t i = 0; i < name.size(); i++){
        if (!isalnum(name[i]))
            return false;
    }
    return true;
}

std::string	Nick::execute(std::string line, User *user, Select &select) {
    std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
    std::cout <<"command is: " << v_cmd[0] << std::endl;
    std::cout <<"command is: " << v_cmd[1] << std::endl;
    std::string nickname = v_cmd[1];

    //ERR_ERRONEUSNICKNAME: erro nickname
    if (nameError(nickname) == false) {
         msg = ERR_ERRONEUSNICKNAME(nickname);
         msg += delimiter;
         return msg;
    }
    //RR_NONICKNAMEGIVEN: don t nickname given
    if (v_cmd.size() != 2 || nickname.length() == 0) {
        std::cout << v_cmd.size() << std::endl;
        msg = ERR_NONICKNAMEGIVEN;
        msg += delimiter;
        return msg;
    }
    //ERR_NICKNAMEINUSE :aleardy use in user
    if (nickinUse(nickname, select.getUsers()) == true) {
            msg = ERR_NICKNAMEINUSE(nickname);
            msg += delimiter;
            return msg;
    }

    msg = ":" + user->getHostname() + " 001 " + nickname + "\r\n";
    user->setNickname(nickname);
    return msg;
}

}
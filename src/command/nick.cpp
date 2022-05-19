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
	std::string msg = user->getPrefix();
	std::vector<std::string> v_cmd = ft_split(line, " ");
	std::string newnick = v_cmd[1];

	//ERR_ERRONEUSNICKNAME: erro nickname
	if (nameError(newnick) == false) {
		msg += ERR_ERRONEUSNICKNAME(newnick) + delimiter;
		select.sendReply(msg, *user);
		return msg;
	}
	//RR_NONICKNAMEGIVEN: don t nickname given
	if (v_cmd.size() != 2 || newnick.length() == 0) {
		msg += ERR_NONICKNAMEGIVEN();
		msg += delimiter;
		select.sendReply(msg, *user);
		return msg;
	}
	//ERR_NICKNAMEINUSE :aleardy use in user
	if (nickinUse(newnick, select.getUsers()) == true) {
		msg += ERR_NICKNAMEINUSE(newnick) + delimiter;
		select.sendReply(msg, *user);
		return msg;
	}
    msg = user->getPrefix() + " NICK " + newnick + delimiter;//tmd
	select.sendReply(msg, *user);
    user->setNickname(newnick);
	
	return msg;
}

}
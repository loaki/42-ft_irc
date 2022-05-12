#include "nick.hpp"

//英文字母，數字
_BEGIN_NS_IRC

Nick::Nick() {}
Nick::~Nick() {}

//ERR_NICKNAMEINUSE :aleardy use in user
bool Nick::nickInUse(std::string name, std::map<int, User> users) {
	std::map<int, User>::iterator it = users.begin();

	for(; it != users.end(); it++) {
		if (it->second.getNickname() == name)
			return true;
	}
	return false;
}

//ERR_ERRONEUSNICKNAME: erro nickname
bool Nick::nameError(std::string name) {
	if(name.length() > MAX_SIZE)
		return false;

	for(size_t i = 0; i < name.size(); i++){
		if (!isalnum(name[i]))
			return false;
	}
	return true;
}

std::string Nick::execute(std::string line, std::map<int, User> users, User user) {
	std::string					msg;
	std::vector<std::string>	v_cmd = ft_split(line, " ");
	std::string					nickname = v_cmd[1];

	if (nameError(nickname) == false) {
		 msg = ERR_ERRONEUSNICKNAME(nickname);
		 msg += DELIM;
		 return msg;
	}

	if (v_cmd.size() != 2 || nickname.length() == 0) {
		msg = ERR_NONICKNAMEGIVEN;
		msg += DELIM;
		return msg;
	}

	if (nickInUse(nickname, users) == true) {
			msg = ERR_NICKNAMEINUSE(nickname);
			msg += DELIM;
			return msg;
	}
	msg = ":" + user.getNickname() + "!" + user.getUsername() + "@"+user.getHostname() + "  " +line ;
	user.setNickname(nickname);

	return msg;
}

_END_NS_IRC
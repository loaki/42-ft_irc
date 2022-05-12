#include "ping.hpp"
#include "select.hpp"

_BEGIN_NS_IRC

Ping::Ping() {}
Ping::~Ping() {}

std::string	Ping::execute(std::string line, std::map<int, User> users, User user) {
	(void)user;
	(void)users;
	std::string					msg;
	std::vector<std::string>	v_cmd = ft_split(line, " ");

	if (v_cmd.size() < 2) {
		msg = ERR_NOORIGIN;
		msg += DELIM;
		return msg;
	}
	msg = "PONG :" + v_cmd[1] + DELIM;
	return msg;
}

_END_NS_IRC
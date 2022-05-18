#include "part.hpp"

namespace irc {

Part::Part() {
	_name = "PART";
}
Part::~Part() {}

std::string	Part::execute(std::string line, User *user, Select &select)
{
	(void)select;
	std::vector<std::string> cmd = irc::ft_split(line, " ");
	(void)user;

	if (cmd.size() < 2)
	{	return ("err");}

	std::string msg = user->getPrefix();
	select.sendReply(msg, user);
	return msg;
}

} 
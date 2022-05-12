#ifndef PING_HPP
# define PING_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

_BEGIN_NS_IRC

class Ping: public Command {
	public:
		Ping();
		~Ping();

		std::string	execute(std::string line, std::map<int, User> users, User user);
};

_END_NS_IRC

#endif
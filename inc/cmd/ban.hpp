#ifndef BAN_HPP
# define BAN_HPP

#include "defs.hpp"
#include "command.hpp"
#include "select.hpp"

namespace irc {
    
    class Ban: public Command {
		Ban();
		virtual ~Ban();

		std::string execute(std::string line, User * user, Select &select);
	};


}

#endif 
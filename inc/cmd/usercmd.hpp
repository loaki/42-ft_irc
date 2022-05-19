#ifndef USERCMD_HPP
# define USERCMD_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

namespace irc {

class Usercmd : public Command {
	public:	
		Usercmd();
		virtual ~Usercmd();

		std::string execute(std::string line, User *user, Select &select);

};


}


#endif 
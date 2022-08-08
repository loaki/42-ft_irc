#ifndef BAN_HPP
# define BAN_HPP

#include "defs.hpp"
#include "command.hpp"
#include "select.hpp"

namespace irc {
    
    class Mode: public Command {
		public:
			Mode();
			virtual ~Mode();
			std::string execute(std::string line, User * user, Select &select);

		private:
			Channel *getChannel(std::string name, Select &select);
			bool isAdmin(Select &select, std::string chan, std::string name);
			
	};


}

#endif 
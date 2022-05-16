#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "defs.hpp"
#include "select.hpp"
#include "user.hpp"
#include "channel.hpp"

namespace irc {

class Select;

class Command {
    public:
        Command() ;
        virtual ~Command();
		
		std::string 		getName() const;
		virtual std::string execute(std::string line, User * user, Select &select) = 0;

    protected:
		std::string			_name;
		std::string			_description;
		// Server*			_server;
		User*		    	_sender;
		std::string      	_args;

    };
}

#endif
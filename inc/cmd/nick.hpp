#ifndef NICK_HPP
# define NICK_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

#define MAX_SIZE 9

_BEGIN_NS_IRC

class Nick: public Command{
	public:
		Nick();
		~Nick();

		bool 		nickInUse(std::string name, std::map<int, User> users);
		bool 		nameError(std::string name);
		std::string	execute(std::string line, std::map<int, User> users, User user);
};














}






#endif
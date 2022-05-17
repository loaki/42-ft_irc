#ifndef LIST_HPP
# define LIST_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

namespace irc
{
	
class List :public Command {
	public :
		List();
		virtual ~List();

		std::string execute(std::string line, User *user, Select &select);



};



} 






#endif
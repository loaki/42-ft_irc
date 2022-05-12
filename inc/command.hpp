#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "defs.hpp"
#include "select.hpp"
#include "user.hpp"

_BEGIN_NS_IRC

class Select;

class Command {
	public:
		Command();
		virtual ~Command();

		std::string			getName() const;
		virtual std::string	execute(std::string line, std::map<int, User> users, User user) = 0;

	protected:
		std::string			_name;
		std::string			_description;
		User				_sender;
		std::string			_args;

};

_END_NS_IRC

#endif
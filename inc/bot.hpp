#ifndef BOT_HPP
#define BOT_HPP

#include "defs.hpp"
#include "select.hpp"
#include "user.hpp"

namespace irc
{

class User;
class Select;

	class Bot : public User {
	public:
		Bot(int fd, std::string pass);
		~Bot();

		void	addBot(Select *sel);
	};

}

#endif
#ifndef KICK_HPP
# define KICK_HPP

#include "defs.hpp"
#include "command.hpp"

namespace irc {

class Kick: public Command {
	public:
		Kick();
		virtual ~Kick();

		std::string  execute(std::string line, User *user, Select &select);

	private:
		Channel *getChannel(std::string name, Select &select);
		bool userInChannel(std::string channelname, std::string name, Select &select);
		bool isChannel(std::string name, Select &select);
		bool checkChannelName(std::string channelname);
};

}

#endif
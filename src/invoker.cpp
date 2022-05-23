#include "invoker.hpp"
#include "select.hpp"

#include "ping.hpp"
#include "nick.hpp"
#include "part.hpp"
#include "privmsg.hpp"
#include "join.hpp"
#include "usercmd.hpp"
#include "kick.hpp"
#include "quit.hpp"
#include "invite.hpp"
#include "notice.hpp"
#include "mode.hpp"

namespace irc {


Invoker::Invoker() {
	_commands.push_back(new Ping());
	_commands.push_back(new Nick());
	_commands.push_back(new Part());
	_commands.push_back(new Privmsg()); 
	_commands.push_back(new Join());
    _commands.push_back(new Kick());
	_commands.push_back(new Quit());
    _commands.push_back(new Invite());
    _commands.push_back(new Notice());
    _commands.push_back(new Mode());
}


Invoker::~Invoker() {
	std::vector<Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++) {
		delete *it;
	}
}

std::string Invoker::parser(std::vector<std::string> Buff, User * user, Select &select)
{
    std::string msg;
    std::vector<std::string>::iterator it = Buff.begin();
    for(;it != Buff.end(); it++) {
        std::vector<std::string> cmd = irc::ft_split(*it, " ");
        for (std::vector<Command*>::iterator i = _commands.begin(); i != _commands.end(); i++)
        {
            if (cmd[0] == (*i)->getName()) {
                msg = ((*i)->execute(*it, user, select));
                return msg;
            }
        }
    }
    return msg;
}

}
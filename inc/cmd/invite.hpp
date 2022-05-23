#ifndef INVITE_HPP
# define INVITE_HPP

#include "defs.hpp"
#include "command.hpp"
#include "select.hpp"

// ERR_NOSUCHNICK
// ERR_NOTONCHANNEL
// ERR_USERONCHANNEL

namespace irc {
    
    class Invite: public Command {
        public:
            Invite();
            virtual ~Invite();

            std::string execute(std::string line, User * user, Select &select);

        private:
            std::string _inviting(std::string to, std::string channel, User * user, Select &select);
            bool suchNick(std::string to, Select &select);
            bool adminOnChannel(Channel *chan, std::string name);
            bool userOnChannel(Channel *chan, std::string name);
            bool isAdmin(Channel *chan, std::string name);
    };

}

#endif
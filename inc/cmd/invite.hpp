#ifndef INVITE_HPP
# define INVITE_HPP

#include "defs.hpp"
#include "command.hpp"

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
            std::string _noSuchNick(std::string to, User * user, Select &select);
            // std::string _notOnCha(std::string channel, User * user);
            // std::string _userOnCha(User * user);
    };

}

#endif
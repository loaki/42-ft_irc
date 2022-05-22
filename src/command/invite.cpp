#include "invite.hpp"

// ERR_NOSUCHNICK       -> ok
// ERR_NOTONCHANNEL
// ERR_USERONCHANNEL
// ERR_CHANOPRIVSNEEDED :You're not channel operator
// RPL_INVITING         -> ok

namespace irc {

// public
    Invite::Invite() { _name = "INVITE"; }
    Invite::~Invite() {}
    
     bool Invite::suchNick(std::string to,  Select &select) {
        int fd = -1;
        
        std::vector<User *> users = select.getUsers();
        std::vector<User *>::iterator it = users.begin();
        std::vector<User *>::iterator ite = users.end();
        for (; it != ite; it++) {
            if ((*it)->getNickname() == to) {
                fd = (*it)->getUserFd();
                return true;
            }
        }
        return false;
    }

    // private
    std::string Invite::_inviting(std::string to, std::string channel, User * user, Select &select) {
        int fd = -1;

        std::string msg1 = user->getPrefix();
        msg1 += " INVITE " + to + " " + channel;
        msg1 += delimiter;
        select.sendReply(msg1, *user);

        std::string msg2 = user->getPrefix();
        msg2 += RPL_INVITING(user->getNickname(), to, channel);
        msg2 += delimiter;
        select.sendReply(msg2, *user);

        std::vector<User *> users = select.getUsers();
        std::vector<User *>::iterator it = users.begin();
        std::vector<User *>::iterator ite = users.end();
        for (; it != ite; it++) {
            if ((*it)->getNickname() == to) {
                fd = (*it)->getUserFd();
                break ;
            }
        }

        std::string msg3;
        msg3 += user->getNickname();
        msg3 += " invites you to ";
        msg3 += channel;
        msg3 += delimiter;
        send(fd, msg3.c_str(), msg3.length(), 0);

        return msg3;
    }
    // bool Invite::onChannel(std::string channel, User * user) {
       
    // }

    // std::string Invite::userOnChanel(User * user) {
            
    // }

    std::string Invite::execute(std::string line, User *user, Select &select) {
        std::string msg;
        
        std::vector<std::string> v_cmd = ft_split(line, " ");

        std::string inviteName = v_cmd[1];
        std::string inviteCha = v_cmd[2];

        if ((this->suchNick(inviteName, select)) == false) {
            msg = user->getPrefix();
            msg += ERR_NOSUCHNICK(user->getNickname(), inviteName);
            msg += delimiter;
            select.sendReply(msg, *user);
            return msg;
        }
        //if (inChannel(inviteCha, user))
        //if (userInChane(user)) {
        //     ERR_USERONCHANNEL
        // }

        return this->_inviting(inviteName, inviteCha, user, select);
    }


   

}

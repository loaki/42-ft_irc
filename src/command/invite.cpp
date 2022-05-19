#include "invite.hpp"

// ERR_NOSUCHNICK       -> ok
// ERR_NOTONCHANNEL
// ERR_USERONCHANNEL
// RPL_INVITING         -> ok

namespace irc {

// public
    Invite::Invite() { _name = "INVITE"; }
    Invite::~Invite() {}
    
    std::string Invite::execute(std::string line, User *user, Select &select) {
        std::string msg;
        std::vector<std::string> v_cmd = ft_split(line, " ");

        std::string inviteName = v_cmd[1];
        std::string inviteCha = v_cmd[2];

        msg = this->_noSuchNick(inviteName, user, select);
        if (msg != "")
            return msg;
        
        return this->_inviting(inviteName, inviteCha, user, select);
    }

// private
    std::string Invite::_inviting(std::string to, std::string channel, User * user, Select &select) {
        int fd = -1;

        std::string msg1 = user->getPrefix();
        msg1 += " INVITE " + to + " " + channel;
        msg1 += delimiter;
        select.sendReply(msg1, *user);

        std::string msg2 = ":127.0.0.1";
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

    std::string Invite::_noSuchNick(std::string to, User * user, Select &select) {
        int fd = -1;
        
        std::vector<User *> users = select.getUsers();
        std::vector<User *>::iterator it = users.begin();
        std::vector<User *>::iterator ite = users.end();
        for (; it != ite; it++) {
            if ((*it)->getNickname() == to) {
                fd = (*it)->getUserFd();
                return std::string("");
            }
        }

        std::string msg = ":127.0.0.1";
        msg += ERR_NOSUCHNICK(user->getNickname(), to);
        msg += delimiter;
        select.sendReply(msg, *user);
        return msg;
    }

    // std::string Invite::_notOnCha(std::string channel, User * user) {

    // }

    // std::string Invite::_userOnCha(User * user) {

    // }

}

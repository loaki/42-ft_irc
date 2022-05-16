#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "defs.hpp"
#include "user.hpp"

namespace irc {   
//一个channel
class user;

class Channel {
    public:
        Channel();
        Channel(std::string channelname);
        ~Channel();
    
        
        void                setChannelName(std::string name);
        User*               getUserInchannel(std::string name);
        User*               getUserInchannel(int fd);
        std::vector<User *> getUsers();
        std::string         getChannelName();
        std::string         getTopic();
       
        void                addUser(User *user);
        void                removeUser(User *user);
        void                printAllUsers();
        bool                isUser(User *user);

        void                MsgToUser(User* user, std::string message);
		void                MsgToChannel(std::string message);

    private:
        std::string         _channelName;
        std::vector<User *> _users;
        std::string         _topic;

};

}



#endif
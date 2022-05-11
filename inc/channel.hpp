#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "defs.hpp"

namespace irc {

class Channel {
    public:
        Channel();
        ~Channel();
    
        void setChannelName(std::string channelName);
        bool isChannelName(std::string Name);

    private:
        std::string _channelName;




};

}



#endif
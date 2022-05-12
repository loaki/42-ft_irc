#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "defs.hpp"

_BEGIN_NS_IRC

class Channel {
    public:
        Channel();
        ~Channel();
    
        void setChannelName(std::string channelName);
        bool isChannelName(std::string Name);

    private:
        std::string _channelName;




};

_END_NS_IRC


#endif
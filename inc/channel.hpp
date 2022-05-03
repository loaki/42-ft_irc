#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "defs.hpp"

namespace irc {



class channel {
    public:
        channel();
        ~channel();
    
        void setChannelName(std::string channelName);
        bool isChannelName(std::string Name);

    private:
        std::string _channelName;



};



}



#endif
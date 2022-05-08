#include "channel.hpp"

namespace irc {

channel::channel(){}
channel::~channel(){}

void channel::setChannelName(std::string channelName){ this->_channelName = channelName;}


// bool channel::isChannelName(std::string name){
//     std::string s = name.substr(0, 1);
//     if (s == "#") {
//         std::string channel = name.substr(1); 
//         // if (channel)
//         // {
            
//         // }
//     }
// }















}
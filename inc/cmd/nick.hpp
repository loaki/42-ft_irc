#ifndef NICK_HPP
# define NICK_HPP

#include "defs.hpp"
#include "select.hpp"

namespace irc {

class Select;

class Nick{
    public:
        Nick(/* args */);
        ~Nick();

        std::string _nick(std::string line, Select &sel);

};














}






#endif
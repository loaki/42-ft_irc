#ifndef NICK_HPP
# define NICK_HPP

#include "defs.hpp"
#include "select.hpp"

#define MAX_SIZE 9

namespace irc {

class Select;

class Nick{
    public:
        Nick(/* args */);
        ~Nick();

        bool nickinUse(std::string name, Select &select);
        bool nameError(std::string name);
        std::string _nick(std::string line, User *user, Select &select);

};














}






#endif
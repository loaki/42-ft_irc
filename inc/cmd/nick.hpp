#ifndef NICK_HPP
# define NICK_HPP

#include "defs.hpp"
#include "select.hpp"
#include "command.hpp"

#define MAX_SIZE 9

namespace irc {

class Nick: public Command{
    public:
        Nick(/* args */);
        ~Nick();

        bool nickinUse(std::string name, Select &select);
        bool nameError(std::string name);
        std::string execute(std::string line, User *user, Select *select);

};














}






#endif
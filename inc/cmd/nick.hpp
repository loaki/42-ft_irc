#ifndef NICK_HPP
# define NICK_HPP

#include "defs.hpp"
#include "command.hpp"

#define MAX_SIZE 9

namespace irc {

class Nick: public Command{
    public:
        Nick();
        virtual ~Nick();

        bool 		nickinUse(std::string name, std::vector<User *> users);
        bool 		nameError(std::string name);
        void        execute(std::string line, User *user, Select &select);

};














}






#endif
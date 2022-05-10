#include "command.hpp"

namespace irc {

Command::Command() {}
Command::~Command() {}

std::string part(std::string line, User * user)
{
    std::vector<std::string> cmd = irc::ft_split(line, " ");
    (void)user;
    if (cmd.size() < 2)
        return("err");
    //remove user from channel
    //set user channel to null
<<<<<<< HEAD
    return (":"+ user->getNickname() + "!@irc.42team" + " " + line+"\r\n");
=======
    // toSend = ":" + nick + "!" + user + "@" + host + " " + buf + EOL;
    return (":"+ user->getNickname() + " PART #lobby"+"\n");
>>>>>>> 5dbaccc70d85af2152ba1f02c7c91e74a1ffbca7
}



std::string Command::parser(std::vector<std::string> Buff, User * user)
{
    std::map<std::string, fct_ptr> commands;
    commands["PART"] = part;

    std::vector<std::string>::iterator it = Buff.begin();
    for(;it != Buff.end(); it++) {
        std::vector<std::string> cmd = irc::ft_split(*it, " ");
        if  (commands.find(cmd[0]) != commands.end())
        {
            std::cout << "cmd:" << (commands[cmd[0]](*it, user))<<std::endl;
            return (commands[cmd[0]](*it, user));
        }
    }
    return ("invalid command");

}

}
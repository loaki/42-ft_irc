#ifndef UTILS_HPP
# define UTILS_HPP

#include "defs.hpp"
#include "user.hpp"
#include <cstdlib>

namespace irc {
// ns begin

    void    exitFailure(const std::string & str);
    std::vector<std::string> ft_split(std::string str, std::string del);
	// std::string		craftId();
	// void		createId(std::vector<User *> users, User * user);


// ns end
}

#endif

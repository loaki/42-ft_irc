#ifndef UTILS_HPP
# define UTILS_HPP

#include "defs.hpp"
#include "user.hpp"
#include <cstdlib>

namespace irc {
// ns begin

    void    					exitFailure(const std::string & str);
    std::vector<std::string>	ft_split(std::string str, std::string del);

// ns end
}

#endif

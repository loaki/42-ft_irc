#ifndef PART_HPP
# define PART_HPP

#include "defs.hpp"
#include "select.hpp"

namespace irc {

class Part {
    public:
        Part();
        virtual ~Part();

        std::string _part(std::string line, User * user);
};

}

#endif
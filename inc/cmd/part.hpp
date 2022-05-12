#ifndef PART_HPP
# define PART_HPP

#include "defs.hpp"

_BEGIN_NS_IRC

class Part {
    public:
        Part();
        ~Part();

        std::string _part(std::string line, User * user);
};

}

#endif
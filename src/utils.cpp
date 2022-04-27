#include "utils.hpp"

namespace webserv {
// ns begin

void    exitFailure(const std::string & str) {
    std::cerr << RED "Exit: " NONE << str << std::endl;
    exit(EXIT_FAILURE);
}

// ns end
}
#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
	
    if (ac != 3) {
        std::cout << "./ircserv <port> <password>" << std::endl;
        return (1);
    }
    
    irc::Select select;
    select.serverStart(atoi(av[1]), av[2]);

    return (0);
}

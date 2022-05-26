#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"
#include <signal.h>

bool active = true;

void	handleSignals(int sig)
{
	std::cout << std::endl << RED "[Quit]" NONE << std::endl;
	if (SIGINT == sig) {
		active = false;
    }
}

int main(int ac, char **av) {

    signal(SIGINT, &handleSignals);

    if (ac != 3) {
        std::cout << "./ircserv <port> <password>" << std::endl;
        return (1);
    }
    int i = 0;
    while (av[1][i])
    {
        if (!isdigit(av[1][i])) {
            std::cout << "Error: Port must be a valid port number" << std::endl;
            return (1);
        }
        i++;
    }
    irc::Select select;
    select.serverStart(atoi(av[1]), av[2]);

    return (0);
}

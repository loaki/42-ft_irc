#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	
	irc::Select	select;
	short		port = atoi(av[1]);
	std::string	password = av[2];

	select.serverStart(port, password);
	
	return (0);
}
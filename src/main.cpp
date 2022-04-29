#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
    (void)av;
    (void)ac;

    irc::Select select;
    select.serverStart();
}

//----users
//----#channel
//----commandes
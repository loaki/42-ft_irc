#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
    (void)av;
    (void)ac;

    webserv::Select select;
    select.serverStart();
}
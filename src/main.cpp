#include "defs.hpp"
#include "socket.hpp"
#include "select.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    webserv::Select select;

    select.serverStart();
}
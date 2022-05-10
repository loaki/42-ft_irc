#ifndef DEFS_HPP
# define DEFS_HPP

// C lib
#include <sys/types.h> 
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <exception>

// C++ lib
#include <iostream>  
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fcntl.h>

// my lib
#include "utils.hpp"
// #include "user.hpp"

# define NONE    "\e[0m"
# define RED     "\e[1;31m"
# define GREEN   "\e[1;32m"

# define SERVER_PORT 8080
# define MAX_BUFF 4096
# define INVALID_FD -1
# define SYSCALL_ERR -1


// #define RPL_WELCOME ":irc.42team 001 ming :Welcome to the Internet Relay Network!xuemingwang@localhost\r\n"
#define RPL_WELCOME(nickname) ":irc.42team 001 " + nickname + " :Welcome to the Internet Relay Network!xuemingwang@localhost\r\n"

// structure

#endif
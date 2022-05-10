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
# define delimiter "\r\n"

#define RPL_WELCOME(nickname) ":irc.42team 001 " + nickname + " :Welcome to the Internet Relay Network!xuemingwang@localhost" + delimiter
/*
** Reply + ERROR
*/
// #define RPL_WELCOME(nickname, username, host) host + "001 :Welcome to the Internet Relay Network " +  nick + "!" + username + "@" + host + delimiter
#define RPL_YOURHOST(servername, version, host) host + "002 :Your host is " + servername + ", running version" +  "ver" + delimiter
#define RPL_CREATED(date, host) host + "003 :This server was created" + date + delimiter
#define RPL_MYINFO(servername, version, umonde, cmonde) host + "004" + "<servername> <version> <available user modes>  <available channel modes>" + delimiter       
#define RPL_BOUNCE(servername, port) host + "005 :Try server " + servername + ", port " + port 

//Command PASS: USER
#define ERR_NEEDMOREPARAMS(command) host + "461 * " command + " :Not enough parameters" + delimiter
#define ERR_ALREADYREGISTRED()  host + "462 * :Unauthorized command (already registered)" + delimiter

//Command: NICK
#define ERR_NONICKNAMEGIVEN() host+ "431 * :No nickname given" + delimiter
#define ERR_ERRONEUSNICKNAME() host +
#define ERR_NICKNAMEINUSE(nick) host + "433 * " + nick + ":Nickname is already in use" + delimiter
#define ERR_NICKCOLLISION() host +
#define ERR_UNAVAILRESOURCE() host +
#define ERR_RESTRICTED() host + "484 * :Your connection is restricted!" + delimiter

// Command: OPER                               
//#define ERR_NEEDMOREPARAMS()
#define RPL_YOUREOPER() host +
#define ERR_PASSWDMISMATCH() host + "464 * :Password incorrect" + delimiter
#define ERR_NOOPERHOST() host +

//Command: MODE               
//#define ERR_NEEDMOREPARAMS()
#define ERR_USERSDONTMATCH() host +
#define ERR_UMODEUNKNOWNFLAG() host +
#define RPL_UMODEIS() host +

//Command: SERVICE 
//#define ERR_ALREADYREGISTRED()       
//#define ERR_ERRONEUSNICKNAME()     
//#define ERR_NEEDMOREPARAMS()    
//#define RPL_YOURHOST()   
//#define RPL_MYINFO()     
#define RPL_YOURESERVICE() host +

//Command: SQUIT   
//#define ERR_NEEDMOREPARAMS()                      
#define ERR_NOPRIVILEGES()
#define ERR_NOSUCHSERVER() host +


//Command: JOIN
//#define ERR_NEEDMOREPARAMS()
//#define ERR_UNAVAILRESOURCE()
#define ERR_BANNEDFROMCHAN() host +
#define ERR_CHANNELISFULL() host +
#define ERR_INVITEONLYCHAN() host +
#define ERR_BADCHANNELKEY() host +
#define ERR_NOSUCHCHANNEL(channel) host + "403 * #" + channel + ":No such channel" + delimiter
#define ERR_BADCHANMASK (channel) host + "476 * #" + channel + ":Bad Channel Mask"
#define ERR_TOOMANYTARGETS () host +
#define ERR_TOOMANYCHANNELS(channel) host + "405 * #" + channel + ":You have joined too many channels" + delimiter
#define RPL_TOPIC() host +

//Command: PART 
//#define ERR_NEEDMOREPARAMS()          
//#define ERR_NOSUCHCHANNEL ()     
#define   ERR_NOTONCHANNEL(channel) host + "442 * " + channel + ":You're not on that channel" + delimiter

//Channel mode message
//#define ERR_NEEDMOREPARAMS    
//#define ERR_CHANOPRIVSNEEDED          
#define ERR_KEYSET
#define ERR_NOCHANMODES                 

#define ERR_USERNOTINCHANNEL(nick, channel) host + "441 * " + nick + " #" + channel + ":They aren't on that channel" + delimiter    
#define ERR_UNKNOWNMODE
#define RPL_CHANNELMODEIS
#define RPL_BANLIST                    
#define RPL_ENDOFBANLIST
#define RPL_EXCEPTLIST                 
#define RPL_ENDOFEXCEPTLIST
#define RPL_INVITELIST                 
#define RPL_ENDOFINVITELIST
#define RPL_UNIQOPIS

//command: TOPIC
//#define ERR_NEEDMOREPARAMS()         
//#define ERR_NOTONCHANNEL()   
//#define RPL_TOPIC()    
#define RPL_NOTOPIC() host +
#define ERR_CHANOPRIVSNEEDED(channel) host + "482 * #" + channel + ":You're not channel operator"
//#define ERR_NOCHANMODES() host+


//Command: NAMES             
//#define ERR_NOSUCHSERVER() 
#define ERR_TOOMANYMATCHES() host +
#define RPL_NAMREPLY() host+       
#define RPL_ENDOFNAMEShost() host+ 

//Command: LIST
//#define ERR_TOOMANYMATCHES()  
//#define ERR_NOSUCHSERVER()  
#define RPL_LIST() host +
#define RPL_LISTEND() host +

//Command: INVITE
//#define ERR_NEEDMOREPARAMS()     
//#define ERR_NOTONCHANNEL()      
//#define ERR_CHANOPRIVSNEEDED()    
#define RPL_INVITING() host +
#define ERR_NOSUCHNICK() host +
#define ERR_USERONCHANNEL() host +
#define RPL_AWAY() host +

//Command: PRIVMSG
//#define ERR_NOSUCHNICK()     
//#define RPL_AWAY()    
//#define ERR_TOOMANYTARGETS() 
#define ERR_NORECIPIENT() host +
#define ERR_CANNOTSENDTOCHAN() host +
#define ERR_WILDTOPLEVEL() host +
#define ERR_NOTEXTTOSEND() host +
#define ERR_NOTOPLEVEL() host +


//Command: VERSION
//#define ERR_NOSUCHSERVER()  
#define RPL_VERSION() host+

//Command: LINKS
//#define ERR_NOSUCHSERVER() 
#define RPL_LINKS()host +
#define RPL_ENDOFLINKS() host+

//Command: CONNECT
//#define ERR_NOSUCHSERVER()
//#define  ERR_NEEDMOREPARAMS() 
//#define ERR_NOPRIVILEGES() 

// Command: ADMIN
//#define ERR_NOSUCHSERVER()
#define RPL_ADMINME()  host+ 
#define RPL_ADMINLOC2() host+ 
#define RPL_ADMINLOC1() host+ 
#define RPL_ADMINEMAIL() host+ 

// Command: INFO                                
//#define ERR_NOSUCHSERVER()
#define RPL_INFO() host+ 
#define RPL_ENDOFINFO() host+

//Command: WHO
//#define ERR_NOSUCHSERVER()
#define RPL_WHOREPLY() host+
#define RPL_ENDOFWHO() host+

//Command: WHOIS
//#define ERR_NOSUCHSERVER() host+
//#define ERR_NONICKNAMEGIVEN() host+
//#define ERR_NOSUCHNICK()  host+
//#define RPL_AWAY() host+
//#define RPL_ENDOFWHOIS() host+
#define RPL_WHOISUSER() host+
#define RPL_WHOISCHANNELS() host+
#define RPL_WHOISSERVER() host+
#define RPL_WHOISIDLE() host+
#define RPL_WHOISOPERATOR() host+

//Command: KILL
//#define ERR_NOPRIVILEGES()   host+
//#define ERR_NOSUCHNICK()  host+
//#define ERR_NEEDMOREPARAMS() host+
#define ERR_CANTKILLSERVER() host+

//Command: PING
//#define ERR_NOSUCHSERVER() host+
#define ERR_NOORIGIN() host+


//Command: PONG
//#define ERR_NOORIGIN()     host+
//#define ERR_NOSUCHSERVER() host+

//Command: USERS   
//#define ERR_NOSUCHSERVER() host+
#define ERR_FILEERROR() host+
#define RPL_USERSSTART() host+          
#define RPL_USERS() host+
#define RPL_NOUSERS() host+           
#define RPL_ENDOFUSERS() host+
#define ERR_USERSDISABLED() host+
// structure

#endif
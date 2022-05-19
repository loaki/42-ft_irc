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
#include <cctype>

// C++ lib
#include <iostream>  
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <cstring>

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

/*
** Reply + ERROR
*/ 
// <nick>!<user>@<host>"  full client identifier
#define RPL_WELCOME(nick, user, host) " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host
#define RPL_YOURHOST(servername, version) " 002 :Your host is " + servername + ", running version" +  "ver"
#define RPL_CREATED(date) " 003 :This server was created" + date
#define RPL_MYINFO(servername, version, umonde, cmonde) " 004 " + " " + servername + " " +version + " " + umond +  " " +cmonde       
#define RPL_BOUNCE(servername, port) " 005 :Try server " + servername + ", port " + port 

//Command PASS: USER
#define ERR_NEEDMOREPARAMS(command) " 461 * " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTRED()  " 462 * :Unauthorized command (already registered)"

//Command: NICK
#define ERR_NONICKNAMEGIVEN " 431 * :No nickname given" 
#define ERR_ERRONEUSNICKNAME(nick) " 432 * " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nick) " 433 * " + nick + " :Nickname is already in use"
#define ERR_NICKCOLLISION(nick) " 436 * " + nick + " :Nickname collision KILL"
#define ERR_UNAVAILRESOURCE(nick) " 437 *" + nick + " :" + nick + " is temporarily unavailable"  //???
#define ERR_RESTRICTED() " 484 * :Your connection is restricted!"

// Command: OPER                               
//#define ERR_NEEDMOREPARAMS()
#define RPL_YOUREOPER() " 381 * " + ":You are now an IRC operator" 
#define ERR_PASSWDMISMATCH() " 464 * :Password incorrect"
#define ERR_NOOPERHOST() " 491 * " + ":No O-lines for your host"

//Command: MODE               
//#define ERR_NEEDMOREPARAMS()
#define ERR_USERSDONTMATCH() " 502 * " + ":Cant change mode for other users"
#define ERR_UMODEUNKNOWNFLAG() " 501 * " +  ":Unknown MODE flag"
#define RPL_UMODEIS(mode)  " 221 * " + mode

//Command: SERVICE 
//#define ERR_ALREADYREGISTRED()       
//#define ERR_ERRONEUSNICKNAME()     
//#define ERR_NEEDMOREPARAMS()    
//#define RPL_YOURHOST()   
//#define RPL_MYINFO()     
#define RPL_YOURESERVICE(nick)  " 383 * " + ":You are service " + nick

//Command: SQUIT   
//#define ERR_NEEDMOREPARAMS()                      
#define ERR_NOPRIVILEGES() " 481 * " +  ":Permission Denied- You're not an IRC operator"
#define ERR_NOSUCHSERVER(server)  " 402 * " + server + " :No such server"


//Command: JOIN
//#define ERR_NEEDMOREPARAMS()
//#define ERR_UNAVAILRESOURCE()
#define ERR_BANNEDFROMCHAN(channel)  " 474 * " + channel + " :Cannot join channel (+b)"
#define ERR_CHANNELISFULL(channel)  " 471 * " + channel + " :Cannot join channel (+l)" //
#define ERR_INVITEONLYCHAN(channel)  " 473 * " + channel + " :Cannot join channel (+i)" //
#define ERR_BADCHANNELKEY(channel)  " 475 * " + channel + " :Cannot join channel (+k)" //
#define ERR_NOSUCHCHANNEL(channel) " 403 * #" + channel + ":No such channel"
#define ERR_BADCHANMASK (channel) " 476 * #" + channel + ":Bad Channel Mask"
#define ERR_TOOMANYTARGETS (target) " 407 * " target + " :Duplicate recipients. No message delivered" //
#define ERR_TOOMANYCHANNELS(channel) " 405 * #" + channel + ":You have joined too many channels"
#define RPL_TOPIC(channel, topic)  " 332 * " + channel + " :" + topic

//Command: PART 
//#define ERR_NEEDMOREPARAMS()          
//#define ERR_NOSUCHCHANNEL ()     
#define   ERR_NOTONCHANNEL(channel) " 442 * " + channel + ":You're not on that channel"

//Channel mode message
//#define ERR_NEEDMOREPARAMS    
//#define ERR_CHANOPRIVSNEEDED 
#define ERR_KEYSET(channel) " 467 * " + channel + " :Channel key already set"
#define ERR_NOCHANMODES(channel) " 477 * " + channel + " :Channel doesn't support modes"       
#define ERR_USERNOTINCHANNEL(nick, channel) " 441 * " + nick + " #" + channel + ":They aren't on that channel"    
#define ERR_UNKNOWNMODE(str) " 472 * " + str + " :is unknown mode char to me"
#define RPL_CHANNELMODEIS(channel, mode, params) " 324 * " + channel + " " + mode + " " + params
#define RPL_BANLIST(channel, banip)  " 367 * " + channel + " " + banip            
#define RPL_ENDOFBANLIST(channel) " 368 * " + channel + " :End of channel ban list"
#define RPL_EXCEPTLIST(channel, mask)  " 348 * " + channel + " " + mask  
#define RPL_ENDOFEXCEPTLIST(channel) " 349 * " + channel + " :End of channel exception list"
#define RPL_INVITELIST (channel, inviter)  " 346 * " + channel + " " + inviter       
#define RPL_ENDOFINVITELIST(channel) " 347 * "channel + " :End of channel invite list"
#define RPL_UNIQOPIS(channel, nick) " 325 * " + channel + " " + nick

//command: TOPIC
//#define ERR_NEEDMOREPARAMS()         
//#define ERR_NOTONCHANNEL()   
//#define RPL_TOPIC()    
//#define ERR_NOCHANMODES()
#define RPL_NOTOPIC(channel) " 331 * " + channel + " :No topic is set"
#define ERR_CHANOPRIVSNEEDED(channel) " 482 * #" + channel + ":You're not channel operator"



//Command: NAMES             
//#define ERR_NOSUCHSERVER() 
#define ERR_TOOMANYMATCHES() "  * " ///???????????
#define RPL_NAMREPLY(chan_mod, channel, nick_list ) " 353 * " + chan_mod + " " + channel + " :" + nick_list   //
#define RPL_ENDOFNAMES(channel) " 366 * " + channel + " :End of /NAMES list" //

//Command: LISTStart
//#define ERR_TOOMANYMATCHES()  
//#define ERR_NOSUCHSERVER()  
#define RPL_LIST(channel, nbrUser, topic) " 322 * " +  channel + " " + nbrUser + " :" + topic
#define RPL_LISTEND() " 323 * " + ":End of /LIST"

//Command: INVITE
//#define ERR_NEEDMOREPARAMS()     
//#define ERR_NOTONCHANNEL()      
//#define ERR_CHANOPRIVSNEEDED()
#define RPL_INVITING(from, to, channel) " 341 " + from + " " + to + " " + channel
#define ERR_NOSUCHNICK(from, to) " 401 " + from + " " + to + " :No such nick"
// #define ERR_NOTONCHANNEL()
#define ERR_USERONCHANNEL(user, channel) " 443 * " + user + " " + channel + " :is already on channel"
// #define RPL_AWAY(nick) " 301 * " + nick + " :" + message

//Command: PRIVMSG
//#define ERR_NOSUCHNICK()     
//#define RPL_AWAY()    
//#define ERR_TOOMANYTARGETS() 
#define ERR_NORECIPIENT(command) " 411 * " + ":No recipient given (" + command + ")"
#define ERR_CANNOTSENDTOCHAN(channel) " 404 * " + channel + " :Cannot send to channel"
#define ERR_WILDTOPLEVEL(mask) " 414 * " + mask + " :Wildcard in toplevel domain"
#define ERR_NOTEXTTOSEND() " 412 * " + ":No text to send"
#define ERR_NOTOPLEVEL(mask) " 413 * " + mask + " :No toplevel domain specified"


//Command: VERSION
//#define ERR_NOSUCHSERVER()  
#define RPL_VERSION(version, server, comments) " 351 * " + version + " " + server + " :" + comments

//Command: LINKS
//#define ERR_NOSUCHSERVER() 
#define RPL_LINKS(mask, server, hopcount, info) " 364 * " + mask + " " + server + " :" + hopcount + " " + info
#define RPL_ENDOFLINKS(mask) " 365 * " + mask + " :End of /LINKS list"

//Command: CONNECT
//#define ERR_NOSUCHSERVER()
//#define  ERR_NEEDMOREPARAMS() 
//#define ERR_NOPRIVILEGES() 

// Command: ADMIN
//#define ERR_NOSUCHSERVER()
#define RPL_ADMINME(server)  " 256 * " + server + " :Administrative info"
#define RPL_ADMINLOC2(info) " 258 * " + ":" + info
#define RPL_ADMINLOC1(info) " 257 * " + ":" + info
#define RPL_ADMINEMAIL(info) " 259 * "  ":" + info

// Command: INFO                                
//#define ERR_NOSUCHSERVER()
#define RPL_INFO(string) " 371 * " + ":" + string
#define RPL_ENDOFINFO() " 374 * " + ":End of /INFO list"

//Command: WHO
//#define ERR_NOSUCHSERVER()
#define RPL_WHOREPLY(channel, user, server, nick, state, real) " 352 * " + channel + " " + user + " " + " " + server + " " + nick + " " + state + " :0 " + real
#define RPL_ENDOFWHO(name) " 315 * " + name + " :End of /WHO list"

//Command: WHOIS
//#define ERR_NOSUCHSERVER() 
//#define ERR_NONICKNAMEGIVEN() 
//#define ERR_NOSUCHNICK()  
//#define RPL_AWAY() 
//#define RPL_ENDOFWHOIS() 
#define RPL_WHOISUSER(nick, user, real) " 311 * " + nick + " " + user + " " + " * :" + real
#define RPL_WHOISCHANNELS(nick, channel)" 319 * " + nick + " :" + channel
#define RPL_WHOISSERVER(nick, server) " 312 * " + nick + " " + server + " :" + info
#define RPL_WHOISIDLE(nick, integer)" 317 * " +  nick + " " + integer + " :seconds idle"
#define RPL_WHOISOPERATOR(nick) " 313 * " nick + " :is an IRC operator"

//Command: KILL
//#define ERR_NOPRIVILEGES()  
//#define ERR_NOSUCHNICK() 
//#define ERR_NEEDMOREPARAMS()
#define ERR_CANTKILLSERVER() " 483 * " + ":You cant kill a server!"

//Command: PING
//#define ERR_NOSUCHSERVER() 
#define ERR_NOORIGIN " 409 * :No origin specified" 


//Command: PONG
//#define ERR_NOORIGIN()    
//#define ERR_NOSUCHSERVER()

//Command: USERS   
//#define ERR_NOSUCHSERVER()
#define ERR_FILEERROR(op, file) " 424 * " + ":File error doing " + op + " on " + file
#define RPL_USERSSTART() " 392 * " + ":UserID Terminal Host"
#define RPL_USERS() " 393 * " + ":%-8s %-9s %-8s"
#define RPL_NOUSERS() " 395 * " + ":Nobody logged in"   
#define RPL_ENDOFUSERS() " 394 * " ":End of users"
#define ERR_USERSDISABLED() " 446 * " + ":USERS has been disabled"
// structure

#endif
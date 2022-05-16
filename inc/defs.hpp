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
#define RPL_WELCOME(nick, user, host) ":irc.42team 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + delimiter
//#define RPL_WELCOME(nick,user,host) ":" + nick + "!" + user + "@" + host + " 001 " + nick + " :Welcome to the Internet Relay" + delimiter
#define RPL_YOURHOST(servername, version) ":irc.42team 002 :Your host is " + servername + ", running version" +  "ver" + delimiter
#define RPL_CREATED(date) ":irc.42team 003 :This server was created" + date + delimiter
#define RPL_MYINFO(servername, version, umonde, cmonde) ":irc.42team 004 " + " " + servername + " " +version + " " + umond +  " " +cmonde + delimiter       
#define RPL_BOUNCE(servername, port) ":irc.42team 005 :Try server " + servername + ", port " + port 

//Command PASS: USER
#define ERR_NEEDMOREPARAMS(command) ":irc.42team 461 * " + command + " :Not enough parameters" + delimiter
#define ERR_ALREADYREGISTRED()  ":irc.42team 462 * :Unauthorized command (already registered)" + delimiter

//Command: NICK
#define ERR_NONICKNAMEGIVEN ":irc.42team 431 * :No nickname given" 
#define ERR_ERRONEUSNICKNAME(nick) ":irc.42team 432 * " + nick + " :Erroneus nickname" + delimiter
#define ERR_NICKNAMEINUSE(nick) ":irc.42team 433 * " + nick + " :Nickname is already in use" + delimiter
#define ERR_NICKCOLLISION(nick) ":irc.42team 436 * " + nick + " :Nickname collision KILL" + delimiter
#define ERR_UNAVAILRESOURCE(nick) ":irc.42team 437 *" + nick + " :" + nick + " is temporarily unavailable"  //???
#define ERR_RESTRICTED() ":irc.42team 484 * :Your connection is restricted!" + delimiter

// Command: OPER                               
//#define ERR_NEEDMOREPARAMS()
#define RPL_YOUREOPER() ":irc.42team 381 * " + ":You are now an IRC operator"  + delimiter
#define ERR_PASSWDMISMATCH() ":irc.42team 464 * :Password incorrect" + delimiter
#define ERR_NOOPERHOST() ":irc.42team 491 * " + ":No O-lines for your host" + delimiter

//Command: MODE               
//#define ERR_NEEDMOREPARAMS()
#define ERR_USERSDONTMATCH() ":irc.42team 502 * " + ":Cant change mode for other users" + delimiter
#define ERR_UMODEUNKNOWNFLAG() ":irc.42team 501 * " +  ":Unknown MODE flag" + delimiter
#define RPL_UMODEIS(mode) host +  "221 * " + mode + delimiter

//Command: SERVICE 
//#define ERR_ALREADYREGISTRED()       
//#define ERR_ERRONEUSNICKNAME()     
//#define ERR_NEEDMOREPARAMS()    
//#define RPL_YOURHOST()   
//#define RPL_MYINFO()     
#define RPL_YOURESERVICE(nick) host +  "383 * " + ":You are service " + nick + delimiter

//Command: SQUIT   
//#define ERR_NEEDMOREPARAMS()                      
#define ERR_NOPRIVILEGES() ":irc.42team 481 * " +  ":Permission Denied- You're not an IRC operator" + delimiter
#define ERR_NOSUCHSERVER(server) host +  "402 * " + server + " :No such server" + delimiter


//Command: JOIN
//#define ERR_NEEDMOREPARAMS()
//#define ERR_UNAVAILRESOURCE()
#define ERR_BANNEDFROMCHAN(channel) host +  "474 * " + channel + " :Cannot join channel (+b)" + delimiter
#define ERR_CHANNELISFULL(channel) host +  "471 * " + channel + " :Cannot join channel (+l)" + delimiter //
#define ERR_INVITEONLYCHAN(channel) host +  "473 * " + channel + " :Cannot join channel (+i)" + delimiter //
#define ERR_BADCHANNELKEY(channel) host +  "475 * " + channel + " :Cannot join channel (+k)" + delimiter //
#define ERR_NOSUCHCHANNEL(channel) ":irc.42team 403 * #" + channel + ":No such channel" + delimiter
#define ERR_BADCHANMASK (channel) ":irc.42team 476 * #" + channel + ":Bad Channel Mask" + delimiter
#define ERR_TOOMANYTARGETS (target) ":irc.42team 407 * " target + " :Duplicate recipients. No message delivered" + delimiter //
#define ERR_TOOMANYCHANNELS(channel) ":irc.42team 405 * #" + channel + ":You have joined too many channels" + delimiter
#define RPL_TOPIC(channel, topic) host +  "332 * " + channel + " :" + topic + delimiter

//Command: PART 
//#define ERR_NEEDMOREPARAMS()          
//#define ERR_NOSUCHCHANNEL ()     
#define   ERR_NOTONCHANNEL(channel) ":irc.42team 442 * " + channel + ":You're not on that channel" + delimiter

//Channel mode message
//#define ERR_NEEDMOREPARAMS    
//#define ERR_CHANOPRIVSNEEDED 
#define ERR_KEYSET(channel) ":irc.42team 467 * " + channel + " :Channel key already set" + delimiter
#define ERR_NOCHANMODES(channel) ":irc.42team 477 * " + channel + " :Channel doesn't support modes" + delimiter       
#define ERR_USERNOTINCHANNEL(nick, channel) ":irc.42team 441 * " + nick + " #" + channel + ":They aren't on that channel" + delimiter    
#define ERR_UNKNOWNMODE(str) ":irc.42team 472 * " + str + " :is unknown mode char to me" + delimiter
#define RPL_CHANNELMODEIS(channel, mode, params) ":irc.42team 324 * " + channel + " " + mode + " " + params + delimiter
#define RPL_BANLIST(channel, banip)  ":irc.42team 367 * " + channel + " " + banip + delimiter            
#define RPL_ENDOFBANLIST(channel) ":irc.42team 368 * " + channel + " :End of channel ban list" + delimiter
#define RPL_EXCEPTLIST(channel, mask)  ":irc.42team 348 * " + channel + " " + mask + delimiter  
#define RPL_ENDOFEXCEPTLIST(channel) ":irc.42team 349 * " + channel + " :End of channel exception list" + delimiter
#define RPL_INVITELIST (channel, inviter)  ":irc.42team 346 * " + channel + " " + inviter + delimiter       
#define RPL_ENDOFINVITELIST(channel) ":irc.42team 347 * "channel + " :End of channel invite list" + delimiter
#define RPL_UNIQOPIS(channel, nick) ":irc.42team 325 * " + channel + " " + nick + delimiter

//command: TOPIC
//#define ERR_NEEDMOREPARAMS()         
//#define ERR_NOTONCHANNEL()   
//#define RPL_TOPIC()    
//#define ERR_NOCHANMODES()
#define RPL_NOTOPIC(channel) ":irc.42team 331 * " + channel + " :No topic is set" + delimiter
#define ERR_CHANOPRIVSNEEDED(channel) ":irc.42team 482 * #" + channel + ":You're not channel operator" + delimiter



//Command: NAMES             
//#define ERR_NOSUCHSERVER() 
#define ERR_TOOMANYMATCHES() ":irc.42team  * " ///???????????
#define RPL_NAMREPLY(chan_mod, channel, nick_list ) host+ "353 * " + chan_mod + " " + channel + " :" + nick_list + delimiter   //
#define RPL_ENDOFNAMES(channel) ":irc.42team 366 * " + channel + " :End of /NAMES list" + delimiter //

//Command: LISTStart
//#define ERR_TOOMANYMATCHES()  
//#define ERR_NOSUCHSERVER()  
#define RPL_LIST(channel, nbrUser, topic) ":irc.42team 322 * " +  channel + " " + nbrUser + " :" + topic + delimiter
#define RPL_LISTEND() ":irc.42team 323 * " + ":End of /LIST" + delimiter

//Command: INVITE
//#define ERR_NEEDMOREPARAMS()     
//#define ERR_NOTONCHANNEL()      
//#define ERR_CHANOPRIVSNEEDED()    
#define RPL_INVITING(nick,channel) ":irc.42team 341 * " + nick + " " + channel + delimiter
#define ERR_NOSUCHNICK(nickname) ":irc.42team 401 * " + nickname + " :No such nick/channel" + delimiter
#define ERR_USERONCHANNEL(user, channel) ":irc.42team 443 * " + user + " " + channel + " :is already on channel" + delimiter
#define RPL_AWAY(nick) ":irc.42team 301 * " + nick + " :" + message + delimiter

//Command: PRIVMSG
//#define ERR_NOSUCHNICK()     
//#define RPL_AWAY()    
//#define ERR_TOOMANYTARGETS() 
#define ERR_NORECIPIENT(command) ":irc.42team 411 * " + ":No recipient given (" + command + ")" + delimiter
#define ERR_CANNOTSENDTOCHAN(channel) ":irc.42team 404 * " + channel + " :Cannot send to channel" + delimiter
#define ERR_WILDTOPLEVEL(mask) ":irc.42team 414 * " + mask + " :Wildcard in toplevel domain" + delimiter
#define ERR_NOTEXTTOSEND() ":irc.42team 412 * " + ":No text to send" + delimiter
#define ERR_NOTOPLEVEL(mask) ":irc.42team 413 * " + mask + " :No toplevel domain specified" + delimiter


//Command: VERSION
//#define ERR_NOSUCHSERVER()  
#define RPL_VERSION(version, server, comments) ":irc.42team 351 * " + version + " " + server + " :" + comments + delimiter

//Command: LINKS
//#define ERR_NOSUCHSERVER() 
#define RPL_LINKS(mask, server, hopcount, info) ":irc.42team 364 * " + mask + " " + server + " :" + hopcount + " " + info + delimiter
#define RPL_ENDOFLINKS(mask) ":irc.42team 365 * " + mask + " :End of /LINKS list" + delimiter

//Command: CONNECT
//#define ERR_NOSUCHSERVER()
//#define  ERR_NEEDMOREPARAMS() 
//#define ERR_NOPRIVILEGES() 

// Command: ADMIN
//#define ERR_NOSUCHSERVER()
#define RPL_ADMINME(server)  ":irc.42team 256 * " + server + " :Administrative info" + delimiter
#define RPL_ADMINLOC2(info) ":irc.42team 258 * " + ":" + info + delimiter
#define RPL_ADMINLOC1(info) ":irc.42team 257 * " + ":" + info + delimiter
#define RPL_ADMINEMAIL(info) ":irc.42team 259 * "  ":" + info + delimiter

// Command: INFO                                
//#define ERR_NOSUCHSERVER()
#define RPL_INFO(string) ":irc.42team 371 * " + ":" + string + delimiter
#define RPL_ENDOFINFO() ":irc.42team 374 * " + ":End of /INFO list" + delimiter

//Command: WHO
//#define ERR_NOSUCHSERVER()
#define RPL_WHOREPLY(channel, user, server, nick, state, real) ":irc.42team 352 * " + channel + " " + user + " " + host + " " + server + " " + nick + " " + state + " :0 " + real + delimiter
#define RPL_ENDOFWHO(name) ":irc.42team 315 * " + name + " :End of /WHO list" + delimiter

//Command: WHOIS
//#define ERR_NOSUCHSERVER() 
//#define ERR_NONICKNAMEGIVEN() 
//#define ERR_NOSUCHNICK()  
//#define RPL_AWAY() 
//#define RPL_ENDOFWHOIS() 
#define RPL_WHOISUSER(nick, user, real) ":irc.42team 311 * " + nick + " " + user + " " + host + " * :" + real + delimiter
#define RPL_WHOISCHANNELS(nick, channel)":irc.42team 319 * " + nick + " :" + channel + delimiter
#define RPL_WHOISSERVER(nick, server) ":irc.42team 312 * " + nick + " " + server + " :" + info + delimiter
#define RPL_WHOISIDLE(nick, integer)":irc.42team 317 * " +  nick + " " + integer + " :seconds idle" + delimiter
#define RPL_WHOISOPERATOR(nick) ":irc.42team 313 * " nick + " :is an IRC operator" + delimiter

//Command: KILL
//#define ERR_NOPRIVILEGES()  
//#define ERR_NOSUCHNICK() 
//#define ERR_NEEDMOREPARAMS()
#define ERR_CANTKILLSERVER() ":irc.42team 483 * " + ":You cant kill a server!" + delimiter

//Command: PING
//#define ERR_NOSUCHSERVER() 
#define ERR_NOORIGIN ":irc.42team 409 * :No origin specified" 


//Command: PONG
//#define ERR_NOORIGIN()    
//#define ERR_NOSUCHSERVER()

//Command: USERS   
//#define ERR_NOSUCHSERVER()
#define ERR_FILEERROR(op, file) ":irc.42team 424 * " + ":File error doing " + op + " on " + file + delimiter
#define RPL_USERSSTART() ":irc.42team 392 * " + ":UserID Terminal Host"+ delimiter
#define RPL_USERS() ":irc.42team 393 * " + ":%-8s %-9s %-8s" + delimiter
#define RPL_NOUSERS() ":irc.42team 395 * " + ":Nobody logged in" + delimiter   
#define RPL_ENDOFUSERS() ":irc.42team 394 * " ":End of users" + delimiter
#define ERR_USERSDISABLED() ":irc.42team 446 * " + ":USERS has been disabled" + delimiter
// structure

#endif
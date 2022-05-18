#include "join.hpp"

namespace irc{

Join::Join(){
	 _name = "JOIN";
}
Join:: ~Join(){}

bool Join::ChannelExist(std::string name, std::vector<Channel *> channels){
	std::vector<Channel *>::iterator it = channels.begin();
	for(; it != channels.end(); it++) {
		if ((*it)->getChannelName() == name) 
			return true;
	}
	return false;
}

// void Join::leaveAllChannels(){

// }

std::string Join::execute(std::string line, User *user, Select &select){
	std::cout << "hello\n";

	int ret = -1;
	std::string msg;
    std::vector<std::string> v_cmd = ft_split(line, " ");
	std::string channelname = v_cmd[1];

	if(v_cmd.size() == 0) {
		// msg = ERR_NEEDMOREPARAMS("JOIN");
		msg += delimiter;
		return msg;
	}
	// if (v_cmd[1] == "0") {
	// 	leaveAllChannels();
	// }
	// msg = RPL_TOPIC(channelname, select.getAllChannel.);
	std::string listname = "";
 	std::vector<Channel *> channels = select.getAllChannel();
	if (channels.size() == 0)
	{
		select.addChannel(channelname);
	}
	channels = select.getAllChannel();
	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::cout <<"chan : "<< (*it)->getChannelName()<<std::endl;
		if ((*it)->getChannelName() == channelname)
		{
			(*(*it)).addUser(user);
 			std::vector<User *> chanUsers = (*it)->getUsers();
			for (std::vector<User*>::iterator it2 = chanUsers.begin(); it2 < chanUsers.end(); it2++)
			{
				std::cout <<"nick : "<< (*it2)->getNickname() <<std::endl;
				listname += (*it2)->getNickname();
				if ((it2) == (chanUsers.end() - 1))
					break;
				listname += " ";
			}

		
		}
	}
	std::cout <<"listname : "<<listname<<std::endl;
	std::string msgself1 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 353 " + user->getNickname() +" = "+ channelname + " : @" + listname + "\r\n";
	std::string msgself2 = ":" + user->getNickname() + "!" + user->getUsername()+ "@" +user->getHostname() + " 366 " + user->getNickname() +" "+ channelname + " :End of /NAMES list"+"\r\n";
	msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " " + line + "\r\n";
 	std::vector<User *> users = select.getUsersInchannel(channelname);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {

		if ((*it)->getUserFd() != user->getUserFd()) // && listname.find((*it)->getNickname()) = 0)
		{
			ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
			if (ret == SYSCALL_ERR) {
				std::cout << "[Send response failed]" << std::endl;
				select.clientDisconn(user->getUserFd());
				return NULL;
			}
		}
		else
		{
			ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
			//check ret
			ret = send((*it)->getUserFd(), msgself1.c_str(), msgself1.length(), 0);
			//check ret
			ret = send((*it)->getUserFd(), msgself2.c_str(), msgself2.length(), 0);
			if (ret == SYSCALL_ERR) {
				std::cout << "[Send response failed]" << std::endl;
				select.clientDisconn(user->getUserFd());
				return NULL;
			}
		}
	}
	return msg;
	
}


/*If a JOIN is successful,(using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.*/

}


 	// std::vector<User *> users = select.getUsers();
	// for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
	// 	std::vector<std::string> name = ft_split(listname, " ");
	// 	for(std::vector<std::string>::iterator nameit = name.begin(); nameit != name.end(); nameit++)
	// 	{
	// 		if (std::strcmp((*nameit).c_str(), (*(*it)).getNickname().c_str()) == 0) {
	// 			if ((*it)->getUserFd() != user->getUserFd()) // && listname.find((*it)->getNickname()) = 0)
	// 			{
	// 				ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
	// 				if (ret == SYSCALL_ERR) {
	// 					std::cout << "[Send response failed]" << std::endl;
	// 					select.clientDisconn(user->getUserFd());
	// 					return NULL;
	// 				}
	// 			}
	// 			else
	// 			{
	// 				ret = send((*it)->getUserFd(), msg.c_str(), msg.length(), 0);
	// 				//check ret
	// 				ret = send((*it)->getUserFd(), msgself1.c_str(), msgself1.length(), 0);
	// 				//check ret
	// 				ret = send((*it)->getUserFd(), msgself2.c_str(), msgself2.length(), 0);
	// 				if (ret == SYSCALL_ERR) {
	// 					std::cout << "[Send response failed]" << std::endl;
	// 					select.clientDisconn(user->getUserFd());
	// 					return NULL;
	// 				}
	// 			}
	// 			break;
	// 		}
	// 	}
		// if ( listname.find((*it)->getNickname()) == std::string::npos)
		// 	continue;

			
	// }
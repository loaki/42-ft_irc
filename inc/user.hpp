#ifndef USER_HPP
#define USER_HPP

#include "defs.hpp"

namespace irc
{

	class User
	{
	public:
		User(int fd);
		~User();

		void setName(std::vector<std::string> Buff);

		void setNickname(std::string name);
		void setUsername(std::string name);
		void setHostname(std::string name);
		void setUserFd(int fd);
		void setAdmin(std::pair<std::string, bool> newAdmin); // admin setter
		void addChannel(std::string channel); // add new channel to user after join

		void setJoinServer(bool join);
		bool getJoinServer();
		std::string getPrefix();

		std::string const &getNickname() const;
		std::string const &getUsername() const;
		std::string const &getHostname() const;
		std::string const &getChannelList() const; // get user-in channel list 
		int const &getUserFd() const;

	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		bool _joinServer;
		std::pair<std::string, bool> _channelAdmin; // user admin attributs
		std::vector<std::string>		_onChannel;		// user on channels

	};

}

#endif
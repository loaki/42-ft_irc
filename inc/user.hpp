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

		void 				setNickname(std::string name);
		void				setUsername(std::string name);
		void 				setHostname(std::string name);
		void				setPass(std::string pass);
		void				setChunk(bool chunk);
		void 				setUserFd(int fd);
		void 				setJoinServer(bool join);
		bool 				getJoinServer();
		std::string			getPrefix();

		void addChannel(std::string channel); // add new channel to user after join

		std::string const&	getNickname() const;
		std::string const&	getUsername() const;
		std::string const&	getHostname() const;
		std::string const&	getPass() const;
		bool const&			getChunk() const;
		std::string const&	getChannelList() const; // get user-in channel list 
		int const&			getUserFd() const;

	protected:
		int 						_fd;
		std::string 				_nickname;
		std::string 				_username;
		std::string 				_hostname;
		bool 						_joinServer;
		std::vector<std::string>	_inChannel;		// user on channels
		bool						_chunk;
		std::string					_pass;
	};

}

#endif
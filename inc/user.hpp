#ifndef USER_HPP
# define USER_HPP

#include "defs.hpp"

namespace irc {

class User {
	public:
		User(int fd);
		~User();

		void setNickname(std::string name);
		void setUsername(std::string name);
		void setHostname(std::string name);
		void setUserId(std::string Id);
		void setUserFd(int fd);
		
		std::string const& getNickname()const;
		std::string const& getUsername()const;
		std::string const& getHostname()const;
		std::string const & getUserId() const;
		int const& getUserFd()const;	
		void setJoinServer(bool join);	

	private:
		int _fd;
		std::string _id;
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		bool		_joinServer;

};

}


#endif
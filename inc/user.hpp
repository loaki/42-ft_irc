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
		void setUserFd(int fd);
		void setUserId(int Id);
		
		std::string const& getNickename()const;
		std::string const& getUsername()const;
		int const& getUserFd()const;
		int const & getUserId() const;

	private:
		int _fd;
		int _id;
		std::string _nickname;
		std::string _username;

};

}


#endif
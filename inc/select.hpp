#ifndef SELECT_HPP
# define SELECT_HPP

#include "defs.hpp"
#include "socket.hpp"
#include "user.hpp"
#include "command.hpp"
#include "channel.hpp"

_BEGIN_NS_IRC

class User;
class Socket;
class Command;

class Select {
	public:
	// public: class init
		Select();
		Select(Select const& src);
		~Select();
		Select& operator=(Select const& rhs);

	// public: method
		void				serverStart(const short& port, const std::string&  password);

	// public: attributs
		std::map<int, User> users;

	private:
	// private: method
		int							max_fd();
		void						clientConn();
		void						clientDisconn(const int clientFd);
		bool						PasswordConnect(std::vector<std::string> buff);
		void						handleReq(const int fd);
		std::vector<std::string>	configBuff();

	// private: attributs
		Socket				serverSocket;
		const std::string	_host;
		fd_set				mainSet;
		fd_set				rSet;
		char				buff[4096];
};

_END_NS_IRC

#endif
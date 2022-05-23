// #ifndef BOT_HPP
// #define BOT_HPP

// #include "defs.hpp"
// #include "user.hpp"

// namespace irc
// {

// 	class Bot : public User
// 	{
// 	public:
// 		Bot(int fd);
// 		~Bot();

// 		void				setBotname(std::string name);

// 		void 				setBotFd(int fd);
// 		void 				setJoinServer(bool join);
// 		bool 				getJoinServer();
// 		std::string			getPrefix();

// 		void addChannel(std::string channel); // add new channel to Bot after join

// 		std::string const&	getBotname() const;

// 		std::string const&	getChannelList() const; // get Bot-in channel list 
// 		int const&			getBotFd() const;

// 	private:
// 		int 						_fd;
// 		std::string 				_nickname;
// 		std::string 				_hostname;
// 		bool 						_joinServer;
// 		std::vector<std::string>	_inChannel;		// user on channels
// 	};

// }

// #endif
#ifndef SELECT_HPP
# define SELECT_HPP

#include "defs.hpp"
#include "socket.hpp"
#include "user.hpp"
#include "command.hpp"
#include "channel.hpp"
#include "invoker.hpp"

namespace irc {
// ns begin
class User;
class Socket;
class Command;
//class Invoker;

class Select {
    public:
    // public: class init
        Select();
        Select(Select const& src);
        ~Select();
        Select& operator=(Select const& rhs);

    // public: method
        void    					serverStart(const short& port, const std::string&  password);
        std::vector<User *> 		getUsers();
        std::vector<Channel *>      getAllChannel();
        void                        addChannel(std::string channelName);
		void						addNewUsr(std::vector<User *> users, std::vector<std::string> Buff);
        void    					clientDisconn(const int clientFd);
        void                        sendReply(std::string msg, User *user);
        Channel *                   getChannelByName(std::string name);
        std::vector<User *>         getUsersInchannel(std::string name);

    private:
    // private: method
        int     					max_fd();
        void    					clientConn();
        // void    					clientDisconn(const int clientFd);
        bool    					PasswordConnect(std::vector<std::string> buff);
        void    					handleReq(const int fd);
        void    					sentToAll(const int fd,  std::string str);
		std::vector<std::string> 	configBuff();
       

    // private: attributs
        Socket              		_serverSocket;
		const std::string			_host;
        std::vector<User *> 		users;
        std::vector<int>   			clientfds;
        fd_set              		mainSet;
        fd_set              		rSet;
        fd_set              		wSet; // currently no use
        char                		buff[4096];
		std::vector<Channel *>		_channels;
		//Invoker					_Invoker;

       
};
	// std::string		addNewUsr(std::vector<User *> users, std::vector<std::string> Buff);
// ns end
}

#endif
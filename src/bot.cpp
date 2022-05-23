#include "bot.hpp"

namespace irc {

Bot::Bot(int fd, std::string pass) : User(fd) {
	setNickname("MrBot");
	setUsername("MrBot");
	setPass(pass);
}

Bot::~Bot(){}

void Bot::addBot(Select *sel) {
	(void)sel;

	std::vector<std::string> Info(3);
	Info[0] = "NICK " + getNickname();
	Info[1] = "PASS " + getPass();
	Info[2] = "USER " + getUsername() + " " + getUsername() + " " + getHostname();
	// for (std::vector<std::string>::iterator it = Info.begin(); it != Info.end(); it++) {
	// 	std::cout << "INFO: " << *it << std::endl;
	// }
	sel->addNewUsr(getUserFd(), Info);
	bool ret = sel->ifJoinServer(getUserFd());
	std::cout << "IS JOIN SERVER RETURN : " << ret << std::endl;
	// Join join;

	// std::string ChannelAdd = "JOIN #botChan\r\n";
	// std::string msg = join.execute(ChannelAdd, this, *sel);
	// std::cout << "BOT MESSAGE ****** " << msg << std::endl;
};

	// Command join;

	// std::string ChannelAdd = "JOIN #botChan\r\n";
	// std::string msg = join.execute(ChannelAdd, this, *sel);

	// Channel botC = (*sel).getChannelByName("#botChan");
	// std::cout << "BOT MESSAGE ****** " << msg << "IS CHAN NAME::::: " << botC->printAllUsers() << std::endl;

}
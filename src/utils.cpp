#include "utils.hpp"

namespace irc {
// ns begin

void	exitFailure(const std::string & str) {
	std::cerr << RED "Exit: " NONE << str << std::endl;
	exit(EXIT_FAILURE);
}

// std::string		craftId() {
// 		std::string s;

// 		static const char alphanum[] =
// 				"0123456789"
// 				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// 				"abcdefghijklmnopqrstuvwxyz";
// 		srand( time( 0 ) );
// 		for (int i = 0; i < 10; ++i) {
// 			s += alphanum[rand() % (sizeof(alphanum) - 1)];
// 		}
// 		return (s);
// }

// void		createId(std::vector<User *> users, User * user) {

// 		user->setUserId(craftId());
// 		for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++) {
// 			if ((user->getUserId() == (*(*it)).getUserId()) && user != (*it)) {
// 				user->setUserId(craftId());
// 				it = users.begin();
// 			}
// 		}
// }

std::vector<std::string> ft_split(std::string str, std::string del){
	std::vector<std::string> values;
	size_t pos;
	while ((pos = str.find(del)) != std::string::npos)
	{
		values.push_back(str.substr(0, pos));
		str.erase(0, pos + del.length());  // delet del 
	}
	values.push_back(str);

	return values;
}



// ns end
}
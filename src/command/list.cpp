#include "list.hpp"

namespace irc {

List::List(){
	_name = "LIST";
}
List:: ~List(){}

// std::string List::execute(std::string line, User *user, Select &select){
// 	(void)user;
	
// 	std::string msg;
// 	std::vector<std::string> v_cmd = ft_split(line, " ");
// 	//channel 
// 	if (v_cmd.size() == 1) {
// 		std::vector<Channel *> channels = select.getAllChannel();
// 		vector<Channel *>::iterator it = channels.begin();
// 		for(; it != channels.end()) {
// 			msg = RPL_LIST((*it).getname(), (*it)->getUsers()->size());
// 			msg += RPL_LISTEND();
// 			msg += delimiter;
// 			return msg;
// 		}
// 	}
// }


}
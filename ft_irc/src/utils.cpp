#include "utils.hpp"

namespace irc {
// ns begin

void	exitFailure(const std::string & str) {
	std::cerr << RED "Exit: " NONE << str << std::endl;
	exit(EXIT_FAILURE);
}

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
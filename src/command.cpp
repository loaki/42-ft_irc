#include "command.hpp"

namespace irc {

Command::Command() {}
Command::~Command() {}

std::string Command::getName() const {
	return _name;
}
}
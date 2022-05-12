#include "command.hpp"

_BEGIN_NS_IRC

Command::Command() {}
Command::~Command() {}

std::string Command::getName() const {
	return _name;
}

_END_NS_IRC
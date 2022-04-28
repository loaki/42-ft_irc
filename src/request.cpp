#include "request.hpp"

// public: class init
Request::Request() {}
Request::Request(Request const& src){ *this = src; }
Request::~Request() {}

Request& Request::operator=(Request const& rhs){
    if (this == &rhs) return *this;
    return *this;
}

// public: getter & setter


// public: method
void                      Request::parse_Request(){}

// private: method
std::vector<std::string>  Request::string_split(const std::string& s, const std::string& delim) {
	std::string					tmp;
	std::vector<std::string>	v;
	std::string					line;
	size_t						pos;

	tmp = s;
	if (delim[0] != '\0' && !s.empty()){
		while ((pos = tmp.find(delim)) != std::string::npos)  { 
			line = tmp.substr(0, pos);  
			if (!tmp.empty())
				v.push_back(line); 
			tmp.erase(0, pos + delim.length()); 
		}
	}
	if (!tmp.empty())  
		v.push_back(tmp); 
	return v;
}

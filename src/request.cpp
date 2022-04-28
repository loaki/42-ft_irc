#include "request.hpp"

// public: class init
Request::Request() {}
Request::Request(Request const& src){ *this = src; }
Request::~Request() {}

Request& Request::operator=(Request const& rhs){
    if (this == &rhs) return *this;

    this->_request = rhs._request;
    return *this;
}

// public: getter & setter
const http_request &       Request::getReq() const { return this->_request; }

// public: method
void Request::parse_Request(std::string buff) {

    std::vector<std::string> get_request;
    size_t pos;
    std::string tmp = buff;
    if ((pos = tmp.find("\r\n\r\n"))!= std::string::npos) {  
        std::string header = tmp.substr(0, pos);   
        get_request = string_split(header, "\r\n"); 
    }
    else
        get_request = string_split(buff, "\r\n");
    if (get_request.empty()){
        perror("request info is wrong");
        return;
    }
    parse_lineRequest(get_request); 
    parse_header(get_request);
    this->_request.body = tmp.substr(pos);
    get_request.clear();
}

// private: method
std::vector<std::string>  Request::string_split(const std::string& s, const std::string& delim) {
	std::string					tmp;
	std::vector<std::string>	v;
	std::string					line;
	size_t						pos;

	tmp = s;
	if (delim[0] != '\0' && !s.empty()){
		while ((pos = tmp.find(delim)) != std::string::npos)  { //可以找到
			line = tmp.substr(0, pos);  //从0位开始到pos 长度
			if (!tmp.empty())
				v.push_back(line); //添加到vector
			tmp.erase(0, pos + delim.length()); //删除已经储存的
		}
	}
	if (!tmp.empty())  
		v.push_back(tmp); //最后一段添加进去
	return v;
}

// parser request line: method+url+version
void Request::parse_lineRequest(std::vector<std::string> &get_request){
    std::vector<std::string> line_request;
    line_request = string_split(get_request[0], " ");
    if (line_request.size() == 3) {
        this->_request.method = line_request[0];
        this->_request.url = line_request[1];
        this->_request.version = line_request[2];
    }
}

//parser header
void Request::parse_header(std::vector<std::string> &get_request){
    std::vector<std::string> tmp;
    for (unsigned int i = 1; i < get_request.size(); i++) { 
        tmp = string_split(get_request.at(i), ":"); 
        if (tmp.size() > 2) {
            std::string tmp_value = tmp[1];
            for(unsigned int j = 2; j < tmp.size(); j++)
                tmp_value += ":" + tmp[j];
            this->_request.header[tmp[0]] = tmp_value;
        }
        else
            this->_request.header[tmp[0]] = tmp[1];
    }
    tmp.clear();
}

int Request::get_content_line(){
    std::string str;
    int len;
    std::map<std::string, std::string>::iterator it = this->_request.header.find("Content-Length");
    if (it != this->_request.header.end())
        str = this->_request.header["Content-Length"];
    len = atoi(str.c_str());
    return len;
}

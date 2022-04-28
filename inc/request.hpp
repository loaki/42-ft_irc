#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "defs.hpp"

class Request {
    public:
    // public: class init
        Request();
        Request(Request const& src);
        ~Request();
        Request& operator=(Request const& rhs);


    // public: methode
        void                        parse_Request();

        
    private:
    // private: method 
        std::vector<std::string>    string_split(const std::string& s, const std::string& delim);
        
};


#endif
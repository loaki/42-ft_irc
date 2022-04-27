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

    // public: getter & setter
        const http_request &        getReq() const;

    // public: methode
        void                        parse_Request(std::string buff);

        
    private:
    // private: method
        int                         get_content_line();
        std::vector<std::string>    string_split(const std::string& s, const std::string& delim);
        void                        parse_lineRequest(std::vector<std::string> &get_request);
        void                        parse_header(std::vector<std::string> &get_request);
        
    // private: attributs
        http_request _request;
        
};


#endif
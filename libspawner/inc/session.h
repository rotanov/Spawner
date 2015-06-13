#pragma once

#include <string>
#include <sstream>

#include "inc/md5/md5.h"

class session_class {
private:
    md5_state_t md5_state;
    session_class();
public:
    session_class(const session_class &session);
    static session_class base_session;
    std::string hash() const;
    operator std::string() const {return hash();}
    template<typename T>
    session_class& operator<< (const T &val) {
        std::ostringstream stringstream_tmp;
        std::string str;

        stringstream_tmp << val;
        str = stringstream_tmp.str();
        md5_append(&md5_state, (md5_byte_t*)str.c_str(), str.length());
        return *this;
    }

};

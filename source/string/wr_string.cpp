#include <wr_string.h>

namespace wrtool {
    namespace string {
        const std::vector<std::string> split(const std::string &str, const std::string &sep)
        {
            std::vector<std::string> str_vec; 
            size_t begin = 0 , end = 0;
            while (true) {
                end = str.find(sep, begin);
                if (std::string::npos == end) {
                    str_vec.push_back(str.substr(begin));
                    break;
                } else {
                    str_vec.push_back(str.substr(begin, end - begin));
                }
                
                begin = end + 1;
            }

            return str_vec;
        }
    }
}

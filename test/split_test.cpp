#include "wr_string.h"
#include <iostream>

int main( )
{
    std::vector<std::string> str_vec;
    std::string str("aaa");

    std::cout << "test begin" << std::endl;
    std::cout << "str[" << str << "] split by [.]" << std::endl;
    str_vec = wrtool::string::split(str, ".");
    for (auto i : str_vec) {
        std::cout << i << std::endl;
    }

    return 0;
}

#pragma once
#include "bhlac_arg_type.h"

namespace bhlac {

    class bhlac_argument {

    public:
        bhlac_argument(std::string content_str, arg_type arg_t);
        std::string getContent(void);
        int getEnum(void);

    private:
        std::string content;
        int enum_code;
    };
}

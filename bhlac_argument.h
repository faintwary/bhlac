#pragma once
#include "bhlac_arg_type.h"

namespace bhlac {

    class bhlac_argument {

    public:
        bhlac_argument(const char *content_str, arg_type arg_t);
        char* getContent(void);
        int getEnum(void);

    private:
        char* content;
        int enum_code;
    };
}

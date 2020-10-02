#include "bhlac_arg_type.h"
#include "bhlac_argument.h"

    bhlac::bhlac_argument::bhlac_argument(const char* content_str, bhlac::arg_type arg_t) {

        enum_code = arg_t.get_enum();
        *content = *content_str;
    }

    char* bhlac::bhlac_argument::getContent(void) {

        return content;
    }

    int bhlac::bhlac_argument::getEnum(void) {

        return enum_code;
    }

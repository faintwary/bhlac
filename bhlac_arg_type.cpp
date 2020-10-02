#include "bhlac_arg_type.h"

    bhlac::arg_type::arg_type(bool dash_starts, bool is_fname, bool bhla) {

        if (dash_starts) {

            enum_code = 0;
            return;
        }

        else if (is_fname && bhla) {

            enum_code = 2;
        }

        else if (is_fname) {

            enum_code = 1;
            return;
        }

        else {

            enum_code = 3;
            return;
        }
    }

    int bhlac::arg_type::get_enum(void) {

        return enum_code;
    }

    // enum_code: number representing an enum
    //
    // 0: command line flag
    // 1: output filename
    // 2: BHLA source filename
    // 3: invalid

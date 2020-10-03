#pragma once

#define BHLAC_INVALID 3
#define BHLAC_BHLA_SOURCE 2
#define BHLAC_OUTPUT_FILENAME 1
#define BHLAC_COMPILER_FLAG 0

namespace bhlac {

    class arg_type {

    public:
        arg_type(bool dash_starts, bool is_fname, bool bhla);

        int get_enum(void);

    private:
        int enum_code;

    };
}

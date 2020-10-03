#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "bhlac_arg_type.h"
#include "bhlac_argument.h"

using namespace bhlac;

constexpr char* CRLF = "\r\n";
constexpr char* TAB = "\t";

bool translate_only_mode = false;
bool output_specified = false;
bool echo_source = false;

//! NOT MY CODE
bool ends_with(std::string const &fullString, std::string const &ending) {

    if (fullString.length() >= ending.length()) {

        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {

        return false;
    }
}

//! NOT MY CODE
bool readFile(std::string fileName, std::vector<std::string>* pVector)
{
    // Open the File
    std::ifstream in(fileName);

    // Check if object is valid
    if(!in)
    {
        return false;
    }

    std::string str;

    // Read the next line from File until it reaches the end.
    while (std::getline(in, str))
    {
        pVector->push_back(str);
    }

    // Close The File
    in.close();

    return true;
}

bool valid_file(const char *fname) {

    if (access(fname, F_OK | R_OK ) != -1)
    {
        return true;
    }
    else return false;
}

bool valid_src(const char *fname) {

    if (ends_with(fname, ".bhla") && valid_file(fname))
    {
        return true;
    }
    else return false;
}

//! NOT MY CODE
bool starts_with(const char *full, const char *start) {

    return (0 == strncmp(full, start, strlen(start)));
}

void compile_err(const char * message) {

    std::cout << "\033[1;37;41merror:\033[0m " << message << CRLF << TAB << "compilation terminated\r\n";
}

int main(int argc, char** argv) {

    if (argc <= 1) {

        compile_err("no input files");
        return 0x66;
    }

    std::vector<std::string> *args = new std::vector<std::string>();

    for (char* c = *++argv; c; c=*++argv) {

        args->push_back(std::string(c));
    }

    std::vector<bhlac_argument> processed_args = std::vector<bhlac_argument>();

    assert(args->size() == argc - 1);

    for (std::string str_iter : *args) {

        arg_type arg_t = arg_type(starts_with(str_iter.c_str(), "-"), valid_file(str_iter.c_str()) || output_specified, valid_src(str_iter.c_str()));

        std::string arg_t_str;

        switch (arg_t.get_enum()) {

            case BHLAC_COMPILER_FLAG:
                arg_t_str = "FLAG";
                break;

            case BHLAC_OUTPUT_FILENAME:
                arg_t_str = "OUTPUT";
                break;

            case BHLAC_BHLA_SOURCE:
                arg_t_str = "BHLA SOURCE";
                break;

            default:
                compile_err("invalid arguments");
                return 0x45;
        }

        if (str_iter == "--asm")
            translate_only_mode = true;

        if (str_iter == "-o")
            output_specified = true;

        if (str_iter == "-es")
            echo_source = true;

        if (str_iter == "--echo-source")
            echo_source = true;

        std::cout << arg_t_str << TAB << TAB << (arg_t_str == "BHLA SOURCE" ? "" : TAB) << str_iter << CRLF;

        processed_args.push_back(bhlac_argument(str_iter, arg_t));
    }

    std::vector<std::vector<std::string>*>* pFileCache = new std::vector<std::vector<std::string>*>();

    delete args;

    for (bhlac_argument arg_iter : processed_args) {

        if (arg_iter.getEnum() == BHLAC_BHLA_SOURCE) {

            std::vector<std::string>* pCache = new std::vector<std::string>();

            if (!readFile(arg_iter.getContent(), pCache)) {

                compile_err("error in reading file " + *(arg_iter.getContent().c_str()));
                return 0;
            }
            else {

                pFileCache->push_back(pCache);
            }
        }
    }

    if (echo_source) {

        std::cout << "Source: " << CRLF << "-=-=-=-=-=-=-=-" << CRLF;

        for (std::vector<std::string>* vector_iter : *pFileCache) {

            for (std::string str_iter : *vector_iter) {

                std::cout << CRLF << str_iter;
            }
            std::cout << CRLF << CRLF << "-=-=-=-=-=-=-=-=-=-=-=-";
        }
    }

    delete pFileCache;

    return 0;
}

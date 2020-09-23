#include <iostream>
#include <string>
#include <vector>
#include <cassert>

constexpr char* CRLF = "\r\n";
constexpr char* TAB = "\t";

bool tl_m = false;


bool ends_with(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) {

        std::cout << "error: no input files" << CRLF << TAB << "compilation terminated\r\n";
        return 0x66;
    }

    std::vector<std::string> args = std::vector<std::string>();

    for (char* c = *++argv; c; c=*++argv) {

        args.push_back(std::string(c));
    }

    assert(args.size() == argc - 1);

    for (std::string str_i : args) {

        std::cout << "ARGUMENT" << TAB << str_i << CRLF;
    }



    return 0;
}

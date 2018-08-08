#include "computor.h"
#include "iostream"

Computor::Computor() { }

Computor::~Computor() { }

Computor &Computor::Instance()
{
    static Computor computor;
    return computor;
}

void Computor::start(std::string equation)
{
    try{
        parser(equation);
    }
    catch (...)
    {
        std::cout << "EXEPTION" << std::endl;
    }

}

void Computor::parser(std::string equation)
{
    std::cout << "parser;      str = " << equation << std::endl;
    std::cmatch result;
//    std::regex_constants::match_flag_type::match_any;
//    std::regex reg("/ ([+-]?(?:(?:\\s*\\d+\\.+\\d+\\s*\\*\\s*X\\^\\d+\\s*)|(?:\\s*\\d+\\s*\\*\\s*X\\^\\d+\\s*)|(?:\\s*\\d+\\s*)|(?:\\s*X\\^\\d+\\s*)|(?:\\s*=\\s*))) /g");
    std::regex reg("([+-]?(?:(?:\\d+)))");
    if(std::regex_match(equation.c_str(), result, reg))
        for (int i = 0; i < result.size(); i++)
            std::cout << result[i] << std::endl;
    else
        std::cout << "EXEPTION" << std::endl;
}

void Computor::parseString(std::string str)
{
    std::cout << "parseString; str = " << str << std::endl;
    std::cmatch result;

    std::regex reg("([+-]?(?:(?: \d+\.+\d+X\^\d+)|(?:\d+X\^\d+)|(?:\d+X)|(?:\d+)|(?:X)))");
    if(std::regex_match(str.c_str(), result, reg))
    {
        parseMember(result[1]);
        str = result[2];
    }
    else
        std::cout << "EXEPTION" << std::endl;
}

void Computor::parseMember(std::string str)
{
    std::cout << "parseMember; str = " << str << std::endl;
//    if(std::regex_match(str.c_str(), result, reg))
//        std::cout << "Good " << result[1] << std::endl;
//    else
//        std::cout << "EXEPTION" << std::endl;
}

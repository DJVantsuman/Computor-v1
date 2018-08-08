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
    parseString(equation);
//    std::cout << "parser;      str = " << equation << std::endl;
//    std::cmatch result;
////    std::regex_constants::match_flag_type::match_any;
////    std::regex reg("/ ([+-]?(?:(?:\\s*\\d+\\.+\\d+\\s*\\*\\s*X\\^\\d+\\s*)|(?:\\s*\\d+\\s*\\*\\s*X\\^\\d+\\s*)|(?:\\s*\\d+\\s*)|(?:\\s*X\\^\\d+\\s*)|(?:\\s*=\\s*))) /g");
//    std::regex reg("([+-]?(?:(?:\\d+)))");
////    if(std::regex_match(equation.c_str(), result, reg))
////        for (int i = 0; i < result.size(); i++)
////            std::cout << result[i] << std::endl;
////    else
////        std::cout << "EXEPTION" << std::endl;
}

void Computor::parseString(std::string str)
{
    std::vector<std::string> members;
    std::string var;
    int f = 1;
    for(int i = 0; i <= str.length(); i++) {
        if((str[i] != '+' && str[i] != '-' && str[i] != '\0') || (members.size() == 0 && var.size() == 0))
        {
            if (str[i] == '=')
            {
                f = 2;
                members.push_back(var);
                var.clear();
                continue;
            }
            if (str[i] != ' ')
                var += str[i];
        }
        else if (var.length() > 0 || (f == 2 && (str[i] == '+' || str[i] == '-')))
        {
            if(var.length() > 0)
            {
                members.push_back(var);
                var.clear();
            }
            if (f == 1)
                var += str[i];
            else if (f == 2)
                if (str[i] == '+')
                    var += '-';
                else
                    var += '+';
        }
    }
    parseMember(members);
}

void Computor::parseMember(std::vector<std::string> members)
{
    std::vector<member> memberList;
    std::cmatch result;
    std::regex reg("([\\+\\-])?"
                    "((\\d+)|(\\d+\\.\\d+))?"
                    "(\\*)?"
                    "(X\\^)"
                    "(\\d+)");
    for(int i = 0; i < members.size(); i++) {
        if (std::regex_match(members[i].c_str(), result, reg))
        {
            std::cout << members[i] << std::endl;
            member var;
            std::string s = (std::string)result[1] + (std::string)result[2];
            if(s != "")
                var.n = std::stod(s);
            else
                var.n = 1;
            for(int i = 0; i < result.size(); i++)
                std::cout << result[i] << std::endl;
//            var.power = std::stoi(result[5]);
            memberList.push_back(var);
        }

//    for(int i = 0; i <= members.size(); i++)
//        std::cout << members[i] << std::endl;
    }
}

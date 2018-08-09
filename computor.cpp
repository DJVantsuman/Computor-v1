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

void Computor::parser(std::string str)
{
    std::cout << str << std::endl;
    std::vector<std::string> members;
    std::string var;
    int t = 0;
    for(int i = 0; i <= str.length(); i++) {
        if((str[i] != '+' && str[i] != '-' && str[i] != '\0') ||
                ((members.size() == 0 || members.size() == t) && var.size() == 0))
        {
            if (str[i] == '=')
            {
                members.push_back(var);
                var.clear();
                t = members.size();
                continue;
            }
            if (str[i] != ' ')
                var += str[i];
        }
        else if (var.length() > 0)
        {
            members.push_back(var);
            var.clear();
            var += str[i];
        }
    }
    parseMember(members, t);
}

void Computor::parseMember(std::vector<std::string> members, int t)
{
    std::vector<member> memberList;
    std::string reducedForm;
    std::cmatch result;
    std::regex reg("([\\+\\-])?"
                    "((\\d+)|(\\d+\\.\\d+))?"
                    "(\\*)?"
                    "(X\\^)"
                    "(\\d+)");
    for(int i = 0; i < members.size(); i++) {
        if (std::regex_match(members[i].c_str(), result, reg))
        {
            member var;
            std::string s;
            if (result[2] == "")
            {
                s = (std::string)result[1] + std::to_string(1);
                var.f = 2;
            }
            else
                s = (std::string)result[1] + (std::string)result[2];
            if(s != "")
                var.n = std::stod(s);
            else
                var.n = 1;
            var.power = std::stoi(result[7]);
            if(i >= t)
                var.n *= -1;
            memberList.push_back(var);
        }
    }
    for(int i = 0; i < memberList.size(); i++) {
        if(memberList[i].f == 1)
        {
            std::string sing;
            if(memberList[i].n > 0 && i > 0)
                sing = (" + " + std::to_string(memberList[i].n) + " * ");
            else if (memberList[i].n < 0 && i > 0)
                sing = (" - " + std::to_string(memberList[i].n * -1) + " * ");
            else
                sing = (std::to_string(memberList[i].n) + " * ");
            reducedForm += sing;
        }
        if(memberList[i].f == 2 && memberList[i].n < 0)
            reducedForm += (" - X^" + std::to_string(memberList[i].power));
        else if (memberList[i].f == 2 && memberList[i].n > 0)
            reducedForm += (" + X^" + std::to_string(memberList[i].power));
        else
            reducedForm += ("X^" + std::to_string(memberList[i].power));
    }
    std::cout << "Reduced form: " << reducedForm << " = 0" <<std::endl;
    culculate(memberList);
}

void Computor::culculate(std::vector<member> memberList)
{
    for(int i = 0; i < memberList.size(); i++) {
        if(memberList[i].power == 0)
            c += memberList[i].n;
        else if(memberList[i].power == 1)
            b += memberList[i].n;
        else if(memberList[i].power == 2)
            a += memberList[i].n;
        else {
            std::cout << "Polynomial degree: " << std::to_string(memberList[i].power) << std::endl;
            std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
            exit(1);
        }
    }
}
